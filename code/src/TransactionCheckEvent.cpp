#include "ActorId.hpp"
#include "TransactionCheckEvent.hpp"
#include "EventType.hpp"

/* Initialize the event type of ActorMovedEvent using the address of the
 * event_type static member variable */
const EventType TransactionCheckEvent::event_type =
  EventType(&TransactionCheckEvent::event_type);

TransactionCheckEvent::TransactionCheckEvent() :
  EventInterface(),
  ship_id(0),
  port_id(0),
  ship_gold(0),
  ship_rum(0),
  port_rum(0),
  rum_request(0),
  cancel(false)
{
}

TransactionCheckEvent::TransactionCheckEvent(ActorId ship_id,
					     ActorId port_id,
					     unsigned int ship_gold,
					     unsigned int ship_rum,
					     unsigned int port_rum,
					     unsigned int rum_request)
  : EventInterface(),
    ship_id(ship_id),
    port_id(port_id),
    ship_gold(ship_gold),
    ship_rum(ship_rum),
    port_rum(port_rum),
    rum_request(rum_request),
    cancel(false)
{
}

TransactionCheckEvent::TransactionCheckEvent(bool cancel) :
  EventInterface(),
  ship_id(0),
  port_id(0),
  ship_gold(0),
  ship_rum(0),
  port_rum(0),
  rum_request(0),
  cancel(cancel)
{
}

TransactionCheckEvent::~TransactionCheckEvent()
{
}
