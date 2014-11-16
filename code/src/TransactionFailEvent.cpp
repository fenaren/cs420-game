#include "ActorId.hpp"
#include "TransactionFailEvent.hpp"
#include "EventType.hpp"

/* Initialize the event type of ActorMovedEvent using the address of the
 * event_type static member variable */
const EventType TransactionFailEvent::event_type =
  EventType(&TransactionFailEvent::event_type);

TransactionFailEvent::TransactionFailEvent() :
  EventInterface(),
  ship_id(0),
  port_id(0),
  ship_gold(0),
  ship_rum(0),
  port_rum(0)
{
}

TransactionFailEvent::TransactionFailEvent(ActorId ship_id,
					   ActorId port_id,
					   unsigned int ship_gold,
					   unsigned int ship_rum,
					   unsigned int port_rum)
  : EventInterface(),
    ship_id(ship_id),
    port_id(port_id),
    ship_gold(ship_gold),
    ship_rum(ship_rum),
    port_rum(port_rum)
{
}

TransactionFailEvent::~TransactionFailEvent()
{
}
