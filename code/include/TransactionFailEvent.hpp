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

  TransactionFailEvent();

  TransactionFailEvent(ActorId ship_id, ActorId port_id, double ship_gold, double ship_rum, double port_rum);

  ~TransactionFailEvent();

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
  void setShipGold(double x);

  /* Ship gold getter */
  double getShipGold() const;

  /* Ship rum setter */
  void setShipRum(double y);

  /* Ship rum getter */
  double getShipRum() const;
  
  /* Port rum setter */
  void setPortRum(double y);

  /* Port rum getter */
  double getPortRum() const;

  /* TransactionFailEvent's event type */
  static const EventType event_type;

private:

  /* Actors associated with this event */
  ActorId ship_id, port_id;

  /* Rum and gold of actors associated with this event */
  double ship_gold;
  double ship_rum;
  double port_rum;
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

inline void TransactionFailEvent::setShipGold(double x)
{
  this->ship_gold = x;
}

inline double TransactionFailEvent::getShipGold() const
{
  return ship_gold;
}

inline void TransactionFailEvent::setShipRum(double y)
{
  this->ship_rum = y;
}

inline double TransactionFailEvent::getShipRum() const
{
  return ship_rum;
}

inline void TransactionFailEvent::setPortRum(double y)
{
  this->port_rum= y;
}

inline double TransactionFailEvent::getPortRum() const
{
  return port_rum;
}


#endif
