#include <SFML/System/Time.hpp>

#include "ActorId.hpp"
#include "Ship.hpp"

Ship::Ship(ActorId actor_id) :
  Actor(actor_id),
  gold(0.0),
  rum(0.0),
  max_rum(10.0),
  rum_rate(1.0)
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
  if(delta_t.asSeconds() = 0.0){
    while(rum < max_rum && rum >= 0.0){
	rum -= rum_rate*delta_t.asSeconds();
    }
    if(rum < 0.0)
      rum = 0.0
    if(rum > 10.0)
      rum = 10.0
  }
}
