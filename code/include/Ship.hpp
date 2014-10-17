#if !defined SHIP_HPP
#define SHIP_HPP

#include <SFML/System/Time.hpp>

#include "Actor.hpp"
#include "ActorId.hpp"

class Ship : public Actor
{
public:

  Ship(ActorId actor_id);

  ~Ship();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);

  double getGold() const;

  void setGold(double gold);

  double getRum() const;

  void setRum(double rum);

  double getMaxRum() const;

  void setMaxRum(double max_rum);

  double getRumRate() const;

  void setRumRate(double rum_rate);

private:

  double gold;

  double rum;

  double max_rum;

  double rum_rate;
  
};

inline double Ship::getGold() const
{
  return gold;
}

inline void Ship::setGold(double gold)
{
  this->gold = gold;
}

inline double Ship::getRum() const
{
  return rum;
}

inline void Ship::setRum(double rum)
{
  this->rum = rum;
}

inline double Ship::getMaxRum() const
{
  return max_rum;
}

inline void Ship::setMaxRum(double max_rum)
{
  this->max_rum = max_rum;
}

inline double Ship::getRumRate() const
{
  return rum_rate;
}

inline void Ship::setRumRate(double rum_rate)
{
  this->rum_rate = rum_rate;
}

#endif
