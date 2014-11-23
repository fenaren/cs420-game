#include "ActorId.hpp"
#include "TransactionCancelEvent.hpp"
#include "EventType.hpp"

/* Initialize the event type of TransactionCancelEvent using the address of the
 * event_type static member variable */
const EventType TransactionCancelEvent::event_type =
  EventType(&TransactionCancelEvent::event_type);

TransactionCancelEvent::TransactionCancelEvent() :
  EventInterface()
{
}

TransactionCancelEvent::~TransactionCancelEvent()
{
}
