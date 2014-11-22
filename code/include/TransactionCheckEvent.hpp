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

  TransactionCheckEvent(ActorId ship_id,
			ActorId port_id,
			unsigned int ship_gold,
			unsigned int ship_rum,
			unsigned int port_rum,
			unsigned int rum_request,
			bool cancel);

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
  
  /* Request Rum setter */
  void setRumRequest(unsigned int y);

  /* Request Rum getter*/
  unsigned int getRumRequest() const;

  void setCancel(bool cancel);

  bool getCancel() const;

  /* TransactionCheckEvent's event type */
  static const EventType event_type;

private:

  /* Actors associated with this event */
  ActorId ship_id, port_id;

  /* Rum and gold of actors associated with this event */
  unsigned int ship_gold;
  unsigned int ship_rum;
  unsigned int port_rum;
  unsigned int rum_request;

  // True if the associated transaction should be cancelled
  bool cancel;
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

inline void TransactionCheckEvent::setShipGold(unsigned int x)
{
  this->ship_gold = x;
}

inline unsigned int TransactionCheckEvent::getShipGold() const
{
  return ship_gold;
}

inline void TransactionCheckEvent::setShipRum(unsigned int y)
{
  this->ship_rum = y;
}

inline unsigned int TransactionCheckEvent::getShipRum() const
{
  return ship_rum;
}

inline void TransactionCheckEvent::setPortRum(unsigned int y)
{
  this->port_rum= y;
}

inline unsigned int TransactionCheckEvent::getPortRum() const
{
  return port_rum;
}

inline void TransactionCheckEvent::setRumRequest(unsigned int y)
{
  this->rum_request= y;
}

inline unsigned int TransactionCheckEvent::getRumRequest() const
{
  return rum_request;
}

inline void TransactionCheckEvent::setCancel(bool cancel)
{
  this->cancel = cancel;
}

inline bool TransactionCheckEvent::getCancel() const
{
  return cancel;
}

#endif
