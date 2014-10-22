#if !defined PORT_HPP
#define PORT_HPP

#include <SFML/System/Time.hpp>

#include "Actor.hpp"
#include "ActorId.hpp"

class Port : public Actor
{
public:

  Port(ActorId actor_id);

  ~Port();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);
  
  double getRum() const;

  void setRum(double rum);

  double getMaxRum() const;

  void setMaxRum(double max_rum);

  double getRumRate() const;

  void setRumRate(double rum_rate);

  bool isBuyPort() const;

private:

  double rum;

  double max_rum;

  double rum_rate;
  
};

inline double Port::getRum() const
{
  return rum;
}

inline void Port::setRum(double rum)
{
  this->rum = rum;
}

inline double Port::getMaxRum() const
{
  return max_rum;
}

inline void Port::setMaxRum(double max_rum)
{
  this->max_rum = max_rum;
}

inline double Port::getRumRate() const
{
  return rum_rate;
}

inline void Port::setRumRate(double rum_rate)
{
  this->rum_rate = rum_rate;
}

inline bool Port::isBuyPort() const
{
  return rum_rate > 0;
}

#endif
