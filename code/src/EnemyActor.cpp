#include "EnemyActor.hpp"

EnemyActor::EnemyActor(ActorId actor_id) :
  Actor(actor_id),
  aggro_range(0),
  seek(sf::Vector2i(0,0)),
  prev_pos(sf::Vector2i(0,0)),
  leader(this),
  need_seek(false),
  follow_offset(sf::Vector2i(0,0)),
  patrolTimer(0.0),
  patrolTimerMin(0.0)
{
}

EnemyActor::~EnemyActor() {
	
}

void EnemyActor::update(const sf::Time& delta_t)
{
	Actor::update(delta_t);
	
	if(delta_t.asSeconds() == 0.0)
		return;
		
	if (getState() == EnemyActor::Patrol || getState() == EnemyActor::Follow)
		patrolTimer -= delta_t.asSeconds();
	if (getState() == EnemyActor::Patrol && patrolTimer <= 0.0) {
		setNeedSeek(true);
		patrolTimer = patrolTimerMin;
	}
}

bool EnemyActor::initialize() {
	patrolTimer = patrolTimerMin;
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

EnemyActor::Type EnemyActor::getType() {
	return type;
}

void EnemyActor::setType(EnemyActor::Type new_type) {
	type = new_type;
}

bool EnemyActor::getNeedSeek() {
	return need_seek;
}

void EnemyActor::setNeedSeek(bool new_need) {
	need_seek = new_need;
}

sf::Vector2i EnemyActor::getPrevPos() {
	return prev_pos;
}

void EnemyActor::setPrevPos(sf::Vector2i new_prev) {
	prev_pos = new_prev;
}

sf::Vector2i EnemyActor::getFollowOffset() {
	return follow_offset;
}

void EnemyActor::setFollowOffset(sf::Vector2i new_offset) {
	follow_offset = new_offset;
}

int EnemyActor::getRumPenalty() {
	return rum_penalty;
}

void EnemyActor::setRumPenalty(int new_rum) {
	rum_penalty = new_rum;
}

EnemyActor* EnemyActor::getLeader() {
	return leader;
}

void EnemyActor::setLeader(EnemyActor* new_leader) {
	leader = new_leader;
}

double EnemyActor::getPatrolTimer() {
	return patrolTimer;
}
	
void EnemyActor::setPatrolTimer(double new_pat_timer) {
	patrolTimer = new_pat_timer;
}
	
double EnemyActor::getPatrolTimerMin() {
	return patrolTimerMin;
}
	
void EnemyActor::setPatrolTimerMin(double new_pat_min) {
	patrolTimerMin = new_pat_min;
	patrolTimer = patrolTimerMin;
}

bool EnemyActor::checkAggroRange(sf::Vector2i pos_checker) {
	if (getPosDifference(getPosition(), pos_checker) <= aggro_range)
		return true;
	else
		return false;
}

int EnemyActor::getPosDifference(sf::Vector2i first, sf::Vector2i second) {
	int check = abs((int) first.x - (int) second.x);
	check += abs((int) first.y - (int) second.y);
	return  check;
}

bool EnemyActor::checkIfAtPosition(sf::Vector2i pos_checker) {
	if ((int) getPositionX() == seek.x && (int) getPositionY() == seek.y)
		return true;
	else
		return false;
}

void EnemyActor::checkState(sf::Vector2i ship_pos) {
	
}