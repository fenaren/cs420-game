#include <SFML/System/Time.hpp>
#include <cmath>
#include <cstdlib>

#include "ActorId.hpp"
#include "Ship.hpp"

Ship::Ship(ActorId actor_id) :
  Actor(actor_id),
  gold(0),
  rum(0),
  max_rum(10),
  rum_rate(1.0),
  rum_time(0.0)
{
}

Ship::~Ship()
{
}

bool Ship::initialize()
{
  return true;
}

void Ship::update(const sf::Time& delta_t)
{
  Actor::update(delta_t);

  // If no time has passed since the last update just leave
  if(delta_t.asSeconds() == 0.0)
  {
    return;
  }

  // Track how much time has passed since the last rum count change, unless rum
  // is up against its limit or rum amount isn't changing
  if ((rum == 0 && rum_rate < 0.0) ||
      (rum == max_rum && rum_rate > 0.0) ||
      rum_rate == 0.0)
  {
    rum_time = 0.0;
  }
  else
  {
    rum_time += delta_t.asSeconds();
  }

  // Should the rum amount change this frame?
  if (rum_rate != 0.0 && rum_time > std::abs(1.0 / rum_rate))
  {
    // How much should be adjust the rum amount by?
    unsigned int delta_rum_abs =
      static_cast<unsigned int>(std::trunc(std::abs(rum_time * rum_rate)));

    // Will the change be positive or negative?
    if (rum_rate > 0.0)
    {
      // Will this change exceed max_rum?  Incidentally if there were no
      // max_rum, this would be where you would cap to avoid overflow on the rum
      // variable
      if (delta_rum_abs > max_rum - rum)
      {
	// Cap it so it doesn't exceed max_rum
	delta_rum_abs = max_rum - rum;
      }

      // Add the delta to the current rum amount
      rum += delta_rum_abs;
    }
    else
    {
      // Will this underflow?
      if (delta_rum_abs > rum)
      {
	// Cap it so it doesn't underflow
	delta_rum_abs = rum;
      }

      // Subtract the delta from the current rum amount
      rum -= delta_rum_abs;
    }

    // We just adjusted the rum by delta_rum_abs, so now we need to subtract
    // from rum_time the amount of time it takes at the current rum rate to
    // accumulate delta_rum_abs amount of rum change.
    rum_time -= static_cast<double>(delta_rum_abs) / std::abs(rum_rate);
  }

  // Track how much time has passed since the last gold count change, unless gold
  // amount isn't changing
  if (gold_rate == 0.0)
  {
    gold_time = 0.0;
  }
  else 
  {
    gold_time += delta_t.asSeconds();
  }

  // Should the gold rate change this frame?
  if (rum == 0.0) {
    gold_rate = -0.2;
  }
  else {
    gold_rate = 0.0;
  }

  // Should the gold amount be changed this frame?
  if (gold_rate != 0.0 && gold_time > std::abs(1.0 / gold_rate))
  {
    // How much should be adjust the gold amount by?
    unsigned int delta_gold_abs =
      static_cast<unsigned int>(std::trunc(std::abs(gold_time * gold_rate)));

    // Will the change be positive or negative?
    if (gold_rate > 0.0)
    {
      // Add the delta to the current rum amount
      gold += delta_gold_abs;
    }
    else
    {
      // Will this underflow?
      if (delta_gold_abs > gold)
      {
        // Cap it so it doesn't underflow
        delta_gold_abs = gold;
      }

      // Subtract the delta from the current gold amount
      gold -= delta_gold_abs;
    }

    // We just adjusted the gold by delta_gold_abs, so now we need to subtract
    // from gold_time the amount of time it takes at the current gold rate to
    // accumulate delta_gold_abs amount of gold change.
    gold_time -= static_cast<double>(delta_gold_abs) / std::abs(gold_rate);
  }

}
