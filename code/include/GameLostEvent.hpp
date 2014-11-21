#ifndef GAMELOSTEVENT_HPP
#define GAMELOSTEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class GameLostEvent : public EventInterface {
  public:
  // constructor and destructors
    GameLostEvent();

    virtual ~GameLostEvent();

    static const EventType event_type;

    // returns event type
    virtual EventType getEventType() const;
};
#endif
