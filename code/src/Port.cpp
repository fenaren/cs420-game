#include <SFML/System/Time.hpp>

#include "ActorId.hpp"
#include "Port.hpp"

Port::Port(ActorId actor_id) :
  Actor(actor_id),
  rum(0.0),
  max_rum(1.0),
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
}
