#ifndef GAMERESTARTEVENT_HPP
#define GAMERESTARTEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class GameRestartEvent : public EventInterface {
  public:
  // constructor and destructors
    GameRestartEvent();

    virtual ~GameRestartEvent();

    static const EventType event_type;

    // returns event type
    virtual EventType getEventType() const;
};
#endif
