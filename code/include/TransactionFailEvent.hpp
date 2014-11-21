#if !defined TRANSACTION_FAIL_EVENT_HPP
#define TRANSACTION_FAIL_EVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "ActorId.hpp"

/* TransactionFailEvent represents the event where a transaction fails.
 * Contains information on ship and port involved. */
class TransactionFailEvent : public EventInterface
{
public:

  enum FailReason
  {
    BUY_EXCEEDS_MAX_SHIP_INVENTORY,
    BUY_NOT_ENOUGH_PORT_INVENTORY,
    BUY_NOT_ENOUGH_GOLD,
    SELL_EXCEEDS_SHIP_INVENTORY
  };

  TransactionFailEvent();

  TransactionFailEvent(ActorId ship_id,
		       ActorId port_id,
		       unsigned int ship_gold,
		       unsigned int ship_rum,
		       unsigned int port_rum,
		       FailReason fail_reason);

  virtual ~TransactionFailEvent();

  virtual EventType getEventType() const;

  /* Ship ID setter */
  void setShipId(ActorId actor_id);

  /* Ship ID getter */
  ActorId getShipId() const;
  
  /* Port ID setter */
  void setPortId(ActorId actor_id);

  /* Port ID getter */
  ActorId getPortId() const;

  /* Ship gold setter */
  void setShipGold(unsigned int x);

  /* Ship gold getter */
  unsigned int getShipGold() const;

  /* Ship rum setter */
  void setShipRum(unsigned int y);

  /* Ship rum getter */
  unsigned int getShipRum() const;
  
  /* Port rum setter */
  void setPortRum(unsigned int y);

  /* Port rum getter */
  unsigned int getPortRum() const;

  void setFailReason(FailReason fail_reason);

  FailReason getFailReason() const;

  /* TransactionFailEvent's event type */
  static const EventType event_type;

private:

  /* Actors associated with this event */
  ActorId ship_id, port_id;

  /* Rum and gold of actors associated with this event */
  unsigned int ship_gold;
  unsigned int ship_rum;
  unsigned int port_rum;

  // Why did the transaction fail?
  FailReason fail_reason;
};

inline EventType TransactionFailEvent::getEventType() const
{
  return event_type;
}

inline void TransactionFailEvent::setShipId(ActorId actor_id)
{
  this->ship_id = actor_id;
}

inline ActorId TransactionFailEvent::getShipId() const
{
  return ship_id;
}

inline void TransactionFailEvent::setPortId(ActorId actor_id)
{
  this->port_id = actor_id;
}

inline ActorId TransactionFailEvent::getPortId() const
{
  return port_id;
}

inline void TransactionFailEvent::setShipGold(unsigned int x)
{
  this->ship_gold = x;
}

inline unsigned int TransactionFailEvent::getShipGold() const
{
  return ship_gold;
}

inline void TransactionFailEvent::setShipRum(unsigned int y)
{
  this->ship_rum = y;
}

inline unsigned int TransactionFailEvent::getShipRum() const
{
  return ship_rum;
}

inline void TransactionFailEvent::setPortRum(unsigned int y)
{
  this->port_rum= y;
}

inline unsigned int TransactionFailEvent::getPortRum() const
{
  return port_rum;
}

inline void TransactionFailEvent::setFailReason(FailReason fail_reason)
{
  this->fail_reason = fail_reason;
}

inline
TransactionFailEvent::FailReason TransactionFailEvent::getFailReason() const
{
  return fail_reason;
}



#endif
