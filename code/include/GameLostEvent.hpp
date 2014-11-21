#ifndef GAMELOSTEVENT_HPP
#define GAMELOSTEVENT_HPP

#include "EventInterface.hpp"
#include "EventType.hpp"
#include "HumanGameView.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

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
