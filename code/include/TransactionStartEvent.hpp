#if !defined TRANSACTION_START_EVENT_HPP
#define TRANSACTION_START_EVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "ActorId.hpp"

/* TransactionStartEvent represents the event where a transaction is checked.
 *  Contains information on ship and port involved. */
class TransactionStartEvent : public EventInterface
{
public:

  TransactionStartEvent();

  TransactionStartEvent(ActorId      ship_id,
			ActorId      port_id,
			unsigned int ship_gold,
			unsigned int ship_rum,
			unsigned int port_rum,
			unsigned int port_price);

  virtual ~TransactionStartEvent();

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

  void setRumPrice(unsigned int rum_price);

  unsigned int getRumPrice() const;

  /* TransactionStartEvent's event type */
  static const EventType event_type;

private:

  /* Actors associated with this event */
  ActorId ship_id, port_id;

  /* Rum and gold of actors associated with this event */
  unsigned int ship_gold;
  unsigned int ship_rum;
  unsigned int port_rum;
  unsigned int rum_price;
};

inline EventType TransactionStartEvent::getEventType() const
{
  return event_type;
}

inline void TransactionStartEvent::setShipId(ActorId actor_id)
{
  this->ship_id = actor_id;
}

inline ActorId TransactionStartEvent::getShipId() const
{
  return ship_id;
}

inline void TransactionStartEvent::setPortId(ActorId actor_id)
{
  this->port_id = actor_id;
}

inline ActorId TransactionStartEvent::getPortId() const
{
  return port_id;
}

inline void TransactionStartEvent::setShipGold(unsigned int x)
{
  this->ship_gold = x;
}

inline unsigned int TransactionStartEvent::getShipGold() const
{
  return ship_gold;
}

inline void TransactionStartEvent::setShipRum(unsigned int y)
{
  this->ship_rum = y;
}

inline unsigned int TransactionStartEvent::getShipRum() const
{
  return ship_rum;
}

inline void TransactionStartEvent::setPortRum(unsigned int y)
{
  this->port_rum= y;
}

inline unsigned int TransactionStartEvent::getPortRum() const
{
  return port_rum;
}

inline void TransactionStartEvent::setRumPrice(unsigned int rum_price)
{
  this->rum_price = rum_price;
}

inline unsigned int TransactionStartEvent::getRumPrice() const
{
  return rum_price;
}

#endif
