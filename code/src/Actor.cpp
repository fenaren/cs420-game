#include "Actor.hpp"
#include "ActorId.hpp"

Actor::Actor(ActorId actor_id) :
  actor_id(actor_id),
  move_time(1.0)
{
}

Actor::~Actor()
{
}
