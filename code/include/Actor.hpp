#if !defined ACTOR_HPP
#define ACTOR_HPP

#include <SFML/System/Time.hpp>

#include "ActorId.hpp"

class Actor
{
public:

  Actor(ActorId actor_id);

  ~Actor();

  virtual bool initialize() = 0;

  virtual void update(const sf::Time& delta_t) = 0;

  ActorId getActorId() const;

  void setActorId(ActorId actor_id);

  unsigned int getPositionX() const;

  void setPositionX(unsigned int x);

  unsigned int getPositionY() const;

  void setPositionY(unsigned int y);

  double getMoveTime() const;

  void setMoveTime(double move_time);

private:

  // ID # of this actor
  ActorId actor_id;

  // Position of actor in map coordinates
  unsigned int x;
  unsigned int y;
  
  // How long between moves is allowed for this actor
  double move_time;
};

inline ActorId Actor::getActorId() const
{
  return actor_id;
}

inline void Actor::setActorId(ActorId actor_id)
{
  this->actor_id = actor_id;
}

inline unsigned int Actor::getPositionX() const
{
  return x;
}

inline void Actor::setPositionX(unsigned int x)
{
  this->x = x;
}

inline unsigned int Actor::getPositionY() const
{
  return y;
}

inline void Actor::setPositionY(unsigned int y)
{
  this->y = y;
}

inline double Actor::getMoveTime() const
{
  return move_time;
}

inline void Actor::setMoveTime(double move_time)
{
  this->move_time = move_time;
}

#endif
