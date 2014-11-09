#include <SFML/System/Time.hpp>

#include "ActorId.hpp"
#include "Port.hpp"

Port::Port(ActorId actor_id) :
  Actor(actor_id),
  rum(0.0),
  max_rum(10.0),
  rum_rate(1.0)
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
  if(delta_t.asSeconds() != 0.0)
  {
    rum += rum_rate*delta_t.asSeconds();

    //fail-safe to prevent rum from exceeding max or min
    if(rum < 0.0)
	rum = 0.0;
    if(rum > max_rum)
	rum = max_rum;
  }
}
