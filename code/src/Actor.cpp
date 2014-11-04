#include <SFML/System/Time.hpp>

#include "Actor.hpp"
#include "ActorId.hpp"

Actor::Actor(ActorId actor_id) :
  actor_id(actor_id),
  x(0),
  y(0),
  move_time(0.0),
  min_move_time(0.0)
{
}

Actor::~Actor()
{
}

void Actor::update(const sf::Time& delta_t)
{
  // Add to the amount of time this actor has gone unmoved
  move_time += delta_t.asSeconds();
}
