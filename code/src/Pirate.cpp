#include "Pirate.hpp"
#include <iostream>

Pirate::Pirate(ActorId actor_id) : EnemyActor(actor_id)
{
	setType(EnemyActor::Pirate);
	setState(EnemyActor::Patrol);
	setSeek(sf::Vector2i(getPositionX(), getPositionY()));
	setPrevPos(getSeek());
	setRumPenalty(2);
	setMinMoveTime(1);
	setAggroRange(4);
	setNeedSeek(true);
	recheckTimer = PATROL_TIMER;
}

bool Pirate::initialize() {
	setNeedSeek(true);
	recheckTimer = PATROL_TIMER;
	freezeTimer = FREEZE_TIMER;
}

void Pirate::update(const sf::Time& delta_t) {
	// causes the pirate to occasionally ask for a new patrol in case it gets stuck
	Actor::update(delta_t);
	if (delta_t.asSeconds() == 0.0)
		return;
		
	if (getState() == EnemyActor::Patrol)
		recheckTimer -= delta_t.asSeconds();
		
	if (getState() == EnemyActor::Stop) 
		freezeTimer -= delta_t.asSeconds();
		
	if (getState() == EnemyActor::Patrol && recheckTimer <= 0.0) {
		setNeedSeek(true);
		recheckTimer = PATROL_TIMER;
	}
	if (getState() == EnemyActor::Stop && freezeTimer <= 0.0) {
		setState(EnemyActor::Patrol);
		setNeedSeek(true);
		freezeTimer = FREEZE_TIMER;
	}
}

void Pirate::checkState(sf::Vector2i ship_pos) {
	if (getState() == EnemyActor::Patrol && checkAggroRange(ship_pos)) {
		setState(EnemyActor::Pursue);
		setMinMoveTime(.75);
		setNeedSeek(true);
	}
	else if (getState() == EnemyActor::Pursue && !checkAggroRange(ship_pos)) {
		setState(EnemyActor::Patrol);
		setMinMoveTime(1.0);
		setNeedSeek(true);
	}
}