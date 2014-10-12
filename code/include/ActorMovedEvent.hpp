#if !defined ACTOR_MOVED_EVENT_HPP
#define ACTOR_MOVED_EVENT_HPP

#include "ActorId.hpp"
#include "EventInterface.hpp"
#include "EventType.hpp"

/* ActorMovedEvent represents the event where an actor moves.  Contains
 * information on which actor moved along with the actor's new location. */
class ActorMovedEvent : public EventInterface
{
public:

  ActorMovedEvent();

  ActorMovedEvent(ActorId actor_id, unsigned int x, unsigned int y);

  ~ActorMovedEvent();

  virtual EventType getEventType() const;

  /* Actor ID setter */
  void setActorId(ActorId actor_id);

  /* Actor ID getter */
  ActorId getActorId() const;

  /* X location setter */
  void setX(unsigned int x);

  /* X location getter */
  unsigned int getX() const;

  /* Y location setter */
  void setY(unsigned int y);

  /* Y location getter */
  unsigned int getY() const;

  /* ActorMovedEvent's event type */
  static const EventType event_type;

private:

  /* Actor associated with this event */
  ActorId actor_id;

  /* Location of actor associated with this event */
  unsigned int x;
  unsigned int y;
};

inline EventType ActorMovedEvent::getEventType() const
{
  return event_type;
}

inline void ActorMovedEvent::setActorId(ActorId actor_id)
{
  this->actor_id = actor_id;
}

inline ActorId ActorMovedEvent::getActorId() const
{
  return actor_id;
}

inline void ActorMovedEvent::setX(unsigned int x)
{
  this->x = x;
}

inline unsigned int ActorMovedEvent::getX() const
{
  return x;
}

inline void ActorMovedEvent::setY(unsigned int y)
{
  this->y = y;
}

inline unsigned int ActorMovedEvent::getY() const
{
  return y;
}

#endif
