#if !defined TRANSACTION_CHECK_EVENT_HPP
#define TRANSACTION_CHECK_EVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "ActorId.hpp"

/* TransactionCheckEvent represents the event where a transaction is checked.
 *  Contains information on ship and port involved. */
class TransactionCheckEvent : public EventInterface
{
public:

  TransactionCheckEvent();

  TransactionCheckEvent(ActorId ship_id, ActorId port_id, double ship_gold, double ship_rum, double port_rum, double rum_request);

  virtual ~TransactionCheckEvent();

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
  
  /* Request Rum setter */
  void setRumRequest(double y);

  /* Request Rum getter*/
  double getRumRequest() const;

  /* TransactionCheckEvent's event type */
  static const EventType event_type;

private:

  /* Actors associated with this event */
  ActorId ship_id, port_id;

  /* Rum and gold of actors associated with this event */
  double ship_gold;
  double ship_rum;
  double port_rum;
  double rum_request;
};

inline EventType TransactionCheckEvent::getEventType() const
{
  return event_type;
}

inline void TransactionCheckEvent::setShipId(ActorId actor_id)
{
  this->ship_id = actor_id;
}

inline ActorId TransactionCheckEvent::getShipId() const
{
  return ship_id;
}

inline void TransactionCheckEvent::setPortId(ActorId actor_id)
{
  this->port_id = actor_id;
}

inline ActorId TransactionCheckEvent::getPortId() const
{
  return port_id;
}

inline void TransactionCheckEvent::setShipGold(double x)
{
  this->ship_gold = x;
}

inline double TransactionCheckEvent::getShipGold() const
{
  return ship_gold;
}

inline void TransactionCheckEvent::setShipRum(double y)
{
  this->ship_rum = y;
}

inline double TransactionCheckEvent::getShipRum() const
{
  return ship_rum;
}

inline void TransactionCheckEvent::setPortRum(double y)
{
  this->port_rum= y;
}

inline double TransactionCheckEvent::getPortRum() const
{
  return port_rum;
}

inline void TransactionCheckEvent::setRumRequest(double y)
{
  this->rum_request= y;
}

inline double TransactionCheckEvent::getRumRequest() const
{
  return rum_request;
}


#endif
