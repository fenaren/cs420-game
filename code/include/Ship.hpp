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
  
  bool getIsInvincible() const;
  
  void setIsInvincible(bool new_invincible);
  
  double getGoldRate() const;

  void setGoldRate(double gold_rate);

private:

  unsigned int gold;

  unsigned int rum;

  unsigned int max_rum;

  double rum_rate;

  double gold_rate;
  
  double rum_time;
  
  bool invincible;

  double gold_time;
  
  const double INVINCIBLE_TIMER = 3.0;
  
  double invincibleTimer;
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

inline bool Ship::getIsInvincible() const {
	return invincible;
}

inline void Ship::setIsInvincible(bool new_invincible) {
	invincible = new_invincible;
}

inline double Ship::getGoldRate() const
{
  return gold_rate;
}

inline void Ship::setGoldRate(double gold_rate)
{
  this->gold_rate = gold_rate;

  // We want to do this to avoid massive gold changes when changing from a low
  // gold rate to a high gold rate
  gold_time = 0.0;
}

#endif
