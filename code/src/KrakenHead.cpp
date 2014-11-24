#include "KrakenHead.hpp"

KrakenHead::KrakenHead(ActorId actor_id) : EnemyActor(actor_id)
{
	
}

bool KrakenHead::initialize() {
	setType(EnemyActor::Kraken);
	setState(EnemyActor::Patrol);
	setSeek(sf::Vector2i(getPositionX(), getPositionY()));
	setPrevPos(getSeek());
	setRumPenalty(3);
	setMinMoveTime(3);
	setPatrolTimerMin(30.0);
	setAggroRange(0);
	setNeedSeek(true);
}

void KrakenHead::update(const sf::Time& delta_t) {
	EnemyActor::update(delta_t);
}

void KrakenHead::checkState(sf::Vector2i ship_pos) {
}