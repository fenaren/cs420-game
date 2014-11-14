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
  if (rum_time > std::abs(1.0 / rum_rate))
  {
    // How much should be adjust the rum amount by?
    int delta_rum = static_cast<int>(std::trunc(rum_time / rum_rate));

    // Would this adjustment cause a rum overflow or underflow?  You can't
    // actually perform the modification to test because that would cause the
    // condition we're trying to test for
    if (delta_rum < 0 && std::abs(delta_rum) > rum)
    {
      // This would underflow, so just set delta_rum so it zeros rum
      delta_rum = -static_cast<int>(rum);
    }
    else if (delta_rum > std::numeric_limits<int>::max() - rum)
    {
      // This would overflow, so just set delta_rum so it maxes out rum
      delta_rum = std::numeric_limits<int>::max() - rum;
    }

    // Perform the adjustment, capping at max_rum
    rum += delta_rum;
    rum = std::min(rum, max_rum);


    //fail-safe to prevent rum from exceeding max or min
    if(rum < 0.0)
	rum = 0.0;
    if(rum > max_rum)
	rum = max_rum;
  }
}
