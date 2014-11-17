#if !defined SHIP_HPP
#define SHIP_HPP

#include <SFML/System/Time.hpp>

#include "Actor.hpp"
#include "ActorId.hpp"

class Ship : public Actor
{
public:

  Ship(ActorId actor_id);

  virtual ~Ship();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);

  unsigned int getGold() const;

  void setGold(unsigned int gold);

  unsigned int getRum() const;

  void setRum(unsigned int rum);

  unsigned int getMaxRum() const;

  void setMaxRum(unsigned int max_rum);

  double getRumRate() const;

  void setRumRate(double rum_rate);

private:

  unsigned int gold;

  unsigned int rum;

  unsigned int max_rum;

  double rum_rate;
  
  double rum_time;
};

inline unsigned int Ship::getGold() const
{
  return gold;
}

inline void Ship::setGold(unsigned int gold)
{
  this->gold = gold;
}

inline unsigned int Ship::getRum() const
{
  return rum;
}

inline void Ship::setRum(unsigned int rum)
{
  this->rum = rum;
}

inline unsigned int Ship::getMaxRum() const
{
  return max_rum;
}

inline void Ship::setMaxRum(unsigned int max_rum)
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

  // We want to do this to avoid massive rum changes when changing from a low
  // rum rate to a high rum rate
  rum_time = 0.0;
}

#endif
