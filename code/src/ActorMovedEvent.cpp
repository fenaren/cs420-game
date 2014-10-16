#include "ActorId.hpp"
#include "ActorMovedEvent.hpp"
#include "EventType.hpp"

/* Initialize the event type of ActorMovedEvent using the address of the
 * event_type static member variable */
const EventType ActorMovedEvent::event_type =
  EventType(&ActorMovedEvent::event_type);

ActorMovedEvent::ActorMovedEvent() :
  EventInterface(),
  actor_id(0),
  x(0),
  y(0)
{
}

ActorMovedEvent::ActorMovedEvent(ActorId actor_id, unsigned int x, unsigned int y)
  : EventInterface(),
    actor_id(actor_id),
    x(x),
    y(y)
{
}

ActorMovedEvent::~ActorMovedEvent()
{
}
