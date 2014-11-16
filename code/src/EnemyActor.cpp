#include "EnemyActor.hpp"

void EnemyActor::update(const sf::Time& delta_t)
{
	Actor::update(delta_t);
}

bool EnemyActor::initialize() {
	return true;
}

EnemyActor::State EnemyActor::getState() {
	return state;
}

void EnemyActor::setState(EnemyActor::State new_state) {
	state = new_state;
}

sf::Vector2i EnemyActor::getSeek() {
	return seek;
}

void EnemyActor::setSeek(sf::Vector2i new_seek) {
	seek = new_seek;
}

int EnemyActor::getAggroRange() {
	return aggro_range;
}

void EnemyActor::setAggroRange(int new_aggro) {
	aggro_range = new_aggro;
}