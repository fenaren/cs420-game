#include "GameLostEvent.hpp"

const EventType GameLostEvent::event_type = EventType(&GameLostEvent::event_type);

GameLostEvent::GameLostEvent()
{
}

GameLostEvent::~GameLostEvent() {
}

EventType GameLostEvent::GameLostEvent::getEventType() const
{
  return event_type;
}
