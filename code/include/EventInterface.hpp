#if !defined EVENT_INTERFACE_HPP
#define EVENT_INTERFACE_HPP

//#include <sstream>

#include "EventType.hpp"

/* Abstract base class for all events */
class EventInterface
{
public:

  EventInterface();

  ~EventInterface();

  /* Derived classes implement this to return a unique identifier for the type
     of event they represent */
  virtual EventType getEventType() const = 0;
  
  /* Returns the time when the event was created? Triggered? */
  /*virtual double getTimeStamp() const = 0;*/

  /* Formats class contents into a text stream */ 
  /*virtual serialize(const std::ostream& o) const = 0;*/

  /* Returns a copy of this event */
  /*virtual EventDataInterface* copy() const = 0;*/
};

#endif
