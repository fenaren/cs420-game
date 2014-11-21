#if !defined AI_CMD_EVENT_HPP
#define AI_CMD_EVENT_HPP

#include "ActorId.hpp"
#include "EventInterface.hpp"
#include "EventType.hpp"
#include <SFML/Graphics.hpp>

class AICmdEvent : public EventInterface {
	
public:
	AICmdEvent();
	AICmdEvent(ActorId actor_id, sf::Vector2i pos);
	
	virtual ~AICmdEvent();
	virtual EventType getEventType() const;
	
	void setActorId(ActorId new_id);
	ActorId getActorId() const;
	
	void setPos(sf::Vector2i new_pos);
	sf::Vector2i getPos() const;
	
	static const EventType event_type;
	
private:
	sf::Vector2i pos;
	ActorId actor_id;
};

#endif