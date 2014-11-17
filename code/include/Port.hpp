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
  
  unsigned int getRum() const;

  void setRum(unsigned int rum);

  unsigned int getMaxRum() const;

  void setMaxRum(unsigned int max_rum);

  double getRumRate() const;

  void setRumRate(double rum_rate);

  unsigned int getRumPrice() const;

  bool const isBuyPort() const;

  // Returns the name of this port
  const std::string& getName() const;

  // Sets the name of this port
  void setName(const std::string& name);

private:

  unsigned int rum;

  unsigned int max_rum;

  double rum_rate;

  // The name of this port
  std::string name;

  // How long it has been since the rum count last changed
  double rum_time;
  
};

inline unsigned int Port::getRum() const
{
  return rum;
}

inline void Port::setRum(unsigned int rum)
{
  this->rum = rum;
}

inline unsigned int Port::getMaxRum() const
{
  return max_rum;
}

inline void Port::setMaxRum(unsigned int max_rum)
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

  // We want to do this to avoid massive rum changes when changing from a low
  // rum rate to a high rum rate
  rum_time = 0.0;
}

inline unsigned int Port::getRumPrice() const
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
