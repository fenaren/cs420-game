#include "AICmdEvent.hpp"

const EventType AICmdEvent::event_type = EventType(&AICmdEvent::event_type);

AICmdEvent::AICmdEvent() :
  EventInterface(),
  actor_id(0),
  pos(sf::Vector2i(0,0))
{
}

AICmdEvent::AICmdEvent(ActorId actor_id, sf::Vector2i pos)
  : EventInterface(),
    actor_id(actor_id),
    pos(pos)
{
}

AICmdEvent::~AICmdEvent() {
	
}

void AICmdEvent::setActorId(ActorId new_id) {
	actor_id = new_id;
}

ActorId AICmdEvent::getActorId() {
	return actor_id;
}

EventType AICmdEvent::getEventType() const {
	return event_type;
}

void AICmdEvent::setPos(sf::Vector2i new_pos) {
	pos = new_pos;
}

sf::Vector2i AICmdEvent::getPos() {
	return pos;
}