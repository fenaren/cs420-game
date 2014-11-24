#include "Merchant.hpp"

Merchant::Merchant(ActorId actor_id) : EnemyActor(actor_id)
{
	
}

bool Merchant::initialize() {
	setType(EnemyActor::Merchant);
	setState(EnemyActor::Patrol);
	setSeek(sf::Vector2i(getPositionX(), getPositionY()));
	setPrevPos(getSeek());
	setRumPenalty(-2);
	setMinMoveTime(1);
	setPatrolTimerMin(20.0);
	setAggroRange(5);
	setNeedSeek(true);
	emptyTimer = EMPTY_TIMER;
}

void Merchant::update(const sf::Time& delta_t) {
	EnemyActor::update(delta_t);
	if (getRumPenalty() == 0.0) {
		emptyTimer -= delta_t.asSeconds();
		if (emptyTimer <= 0.0) {
			emptyTimer = EMPTY_TIMER;
			setRumPenalty(-2);
		}
	}
}

void Merchant::checkState(sf::Vector2i ship_pos) {
	if (getState() == EnemyActor::Patrol && checkAggroRange(ship_pos)) {
		setState(EnemyActor::Flee);
		setMinMoveTime(.9);
		setNeedSeek(true);
	}
	else if (getState() == EnemyActor::Flee && !checkAggroRange(ship_pos)) {
		setState(EnemyActor::Patrol);
		setMinMoveTime(1.0);
		setNeedSeek(true);
	}
}