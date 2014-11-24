#include "GameRestartEvent.hpp"

const EventType GameRestartEvent::event_type = EventType(&GameRestartEvent::event_type);

GameRestartEvent::GameRestartEvent()
{
}

GameRestartEvent::~GameRestartEvent() {
}

EventType GameRestartEvent::GameRestartEvent::getEventType() const
{
  return event_type;
}
