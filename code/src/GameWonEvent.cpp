#include "GameWonEvent.hpp"

const EventType GameWonEvent::event_type = EventType(&GameWonEvent::event_type);

GameWonEvent::GameWonEvent()
{
}

GameWonEvent::~GameWonEvent() {
}

EventType GameWonEvent::GameWonEvent::getEventType() const
{
  return event_type;
}
