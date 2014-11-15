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

  TransactionStartEvent(ActorId ship_id,
			ActorId port_id,
			double ship_gold,
			double ship_rum,
			double ship_max_rum,
			double port_rum);

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
  void setShipGold(double x);

  /* Ship gold getter */
  double getShipGold() const;

  /* Ship rum setter */
  void setShipRum(double y);

  /* Ship rum getter */
  double getShipRum() const;
 
  /* Ship max rum setter */
  void setShipMaxRum(double z);

  /* Ship max rum getter */
  double getShipMaxRum() const;
 
  /* Port rum setter */
  void setPortRum(double y);

  /* Port rum getter */
  double getPortRum() const;

  /* TransactionStartEvent's event type */
  static const EventType event_type;

private:

  /* Actors associated with this event */
  ActorId ship_id, port_id;

  /* Rum and gold of actors associated with this event */
  double ship_gold;
  double ship_rum;
  double ship_max_rum;
  double port_rum;
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

inline void TransactionStartEvent::setShipGold(double x)
{
  this->ship_gold = x;
}

inline double TransactionStartEvent::getShipGold() const
{
  return ship_gold;
}

inline void TransactionStartEvent::setShipRum(double y)
{
  this->ship_rum = y;
}

inline double TransactionStartEvent::getShipRum() const
{
  return ship_rum;
}

inline void TransactionStartEvent::setShipMaxRum(double z)
{
  this->ship_max_rum = z;
}

inline double TransactionStartEvent::getShipMaxRum() const
{
  return ship_max_rum;
}

inline void TransactionStartEvent::setPortRum(double y)
{
  this->port_rum= y;
}

inline double TransactionStartEvent::getPortRum() const
{
  return port_rum;
}


#endif
