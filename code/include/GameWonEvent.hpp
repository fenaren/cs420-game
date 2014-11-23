#ifndef GAMEWONEVENT_HPP
#define GAMEWONEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"

class GameWonEvent : public EventInterface {
  public:
  // constructor and destructors
    GameWonEvent();

    virtual ~GameWonEvent();

    static const EventType event_type;

    // returns event type
    virtual EventType getEventType() const;
};
#endif
