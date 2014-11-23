#include "KrakenTentacle.hpp"

KrakenTentacle::KrakenTentacle(ActorId actor_id) : EnemyActor(actor_id)
{
	
}

bool KrakenTentacle::initialize() {
	setType(EnemyActor::Tentacle);
	setState(EnemyActor::Follow);
	setSeek(sf::Vector2i(getPositionX(), getPositionY()));
	setPrevPos(getSeek());
	setRumPenalty(3);
	setMinMoveTime(1);
	setPatrolTimerMin(2);
	setAggroRange(0);
	setNeedSeek(true);
}

void KrakenTentacle::update(const sf::Time& delta_t) {
	EnemyActor::update(delta_t);
}

void KrakenTentacle::checkState(sf::Vector2i ship_pos) {
}