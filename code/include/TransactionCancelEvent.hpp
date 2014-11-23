#if !defined TRANSACTION_CANCEL_EVENT_HPP
#define TRANSACTION_CANCEL_EVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "ActorId.hpp"

// TransactionCancelEvent represents the event where a transaction is cancelled.
class TransactionCancelEvent : public EventInterface
{
public:

  TransactionCancelEvent();

  virtual ~TransactionCancelEvent();

  virtual EventType getEventType() const;

  /* TransactionCancelEvent's event type */
  static const EventType event_type;

};

inline EventType TransactionCancelEvent::getEventType() const
{
  return event_type;
}

#endif
