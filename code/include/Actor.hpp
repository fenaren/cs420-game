#if !defined ACTOR_HPP
#define ACTOR_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include "ActorId.hpp"

class Actor
{
public:

  Actor(ActorId actor_id);

  virtual ~Actor();

  virtual bool initialize() = 0;

  virtual void update(const sf::Time& delta_t);

  ActorId getActorId() const;

  void setActorId(ActorId actor_id);

  unsigned int getPositionX() const;

  void setPositionX(unsigned int x);

  unsigned int getPositionY() const;

  void setPositionY(unsigned int y);

  double getMoveTime() const;

  void setMoveTime(double move_time);

  double getMinMoveTime() const;

  void setMinMoveTime(double min_move_time);
  
  sf::Vector2i getPosition() const;
  
  void setPosition(sf::Vector2i new_pos);

private:

  // ID # of this actor
  ActorId actor_id;

  // Position of actor in map coordinates, not sure if this is how we want to
  // represent position
  unsigned int x;
  unsigned int y;
  
  // How long it's been since the last time this actor was allowed to move
  double move_time;

  // The amount of time that has to pass before this actor will be allowed to
  // move
  double min_move_time;
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

inline double Actor::getMinMoveTime() const
{
  return min_move_time;
}

inline void Actor::setMinMoveTime(double min_move_time)
{
  this->min_move_time = min_move_time;
}

inline sf::Vector2i Actor::getPosition() const {
	return sf::Vector2i((int) x, (int) y);
}

inline void Actor::setPosition(sf::Vector2i new_pos) {
	x = new_pos.x;
	y = new_pos.y;
}

#endif
