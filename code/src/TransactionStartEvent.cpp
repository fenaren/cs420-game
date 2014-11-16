#include "ActorId.hpp"
#include "TransactionStartEvent.hpp"
#include "EventType.hpp"

/* Initialize the event type of ActorMovedEvent using the address of the
 * event_type static member variable */
const EventType TransactionStartEvent::event_type =
  EventType(&TransactionStartEvent::event_type);

TransactionStartEvent::TransactionStartEvent() :
  EventInterface(),
  ship_id(0),
  port_id(0),
  ship_gold(0),
  ship_rum(0),
  port_rum(0),
  rum_price(0)
{
}

TransactionStartEvent::TransactionStartEvent(ActorId ship_id, ActorId port_id, double ship_gold, double ship_rum, double port_rum, unsigned int rum_price)
  : EventInterface(),
    ship_id(ship_id),
    port_id(port_id),
    ship_gold(ship_gold),
    ship_rum(ship_rum),
    port_rum(port_rum),
    rum_price(rum_price)
{
}

TransactionStartEvent::~TransactionStartEvent()
{
}
