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
}

void Pirate::checkState(sf::Vector2i ship_pos) {
	if (checkAggroRange(ship_pos)) {
		setState(EnemyActor::Pursue);
		setMinMoveTime(.75);
		setNeedSeek(true);
	}
	else if (getState() == EnemyActor::Pursue) {
		setState(EnemyActor::Patrol);
		setMinMoveTime(1.0);
		setNeedSeek(true);
	}
}