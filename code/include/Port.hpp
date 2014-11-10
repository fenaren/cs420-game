#if !defined PORT_HPP
#define PORT_HPP

#include <algorithm>
#include <SFML/System/Time.hpp>
#include <string>

#include "Actor.hpp"
#include "ActorId.hpp"

class Port : public Actor
{
public:

  Port(ActorId actor_id);

  virtual ~Port();

  virtual bool initialize();

  virtual void update(const sf::Time& delta_t);
  
  double getRum() const;

  void setRum(double rum);

  double getMaxRum() const;

  void setMaxRum(double max_rum);

  double getRumRate() const;

  void setRumRate(double rum_rate);

  double getRumPrice() const;

  bool const isBuyPort() const;

  // Returns the name of this port
  const std::string& getName() const;

  // Sets the name of this port
  void setName(const std::string& name);

private:

  double rum;

  double max_rum;

  double rum_rate;

  // The name of this port
  std::string name;
  
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

inline double Port::getRumPrice() const
{
  return std::min(max_rum - rum + 1.0, 10.0);
}

inline const bool Port::isBuyPort() const
{
  return rum_rate > 0;
}

inline const std::string& Port::getName() const
{
  return name;
}

inline void Port::setName(const std::string& name)
{
  this->name = name;
}

#endif
