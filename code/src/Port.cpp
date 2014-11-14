#include <SFML/System/Time.hpp>
#include <cmath>
#include <cstdlib>
#include <limits>

#include "ActorId.hpp"
#include "Port.hpp"

Port::Port(ActorId actor_id) :
  Actor(actor_id),
  rum(0),
  max_rum(10),
  rum_rate(1.0),
  rum_time(0)
{
}

Port::~Port()
{
}

bool Port::initialize()
{
  return true;
}

void Port::update(const sf::Time& delta_t)
{
  Actor::update(delta_t);

  // If no time has passed since the last update just leave
  if(delta_t.asSeconds() == 0.0)
  {
    return;
  }
   
  // Track how much time has passed since the last rum count change
  rum_time += delta_t.asSeconds();

  // Should the rum amount change this frame?
  if (rum_rate != 0.0 && rum_time > std::abs(1.0 / rum_rate))
  {
    // How much should be adjust the rum amount by?
    unsigned int delta_rum_abs =
      static_cast<unsigned int>(std::trunc(std::abs(rum_time * rum_rate)));

    // Will the change be positive or negative?
    if (rum_rate > 0.0)
    {
      // Will this overflow?
      if (delta_rum_abs > std::numeric_limits<unsigned int>::max() - rum)
      {
	// Cap it so it doesn't overflow
	delta_rum_abs = std::numeric_limits<unsigned int>::max() - rum;
      }
    }
    else
    {
      // Will this underflow?
      if (delta_rum_abs > rum)
      {
	// Cap it so it doesn't underflow
	delta_rum_abs = rum;
      }
    }

    // Perform the adjustment, capping at max_rum
    /*rum += delta_rum;
    rum = std::min(rum, max_rum);


    //fail-safe to prevent rum from exceeding max or min
    if(rum < 0.0)
	rum = 0.0;
    if(rum > max_rum)
    rum = max_rum;*/
  }
}
