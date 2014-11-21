#include "AIGameView.hpp"
#include <iostream>

AIGameView::AIGameView(GameLogic* game_logic) :
  GameView(game_logic)
{
}

AIGameView::~AIGameView() {
	
}

bool AIGameView::initialize() {
	return true;
}

// AIGameView first calls each enemies check state function to
// see if it switches states
//
// Then, it updates the seek on each enemy that needs it
//
// For example, Pursue would be passed the ship's pos
// while patrol would be passed the next waypoint if it 
// already reached its current
//
// Finally, for every enemy that can move (move time
// is correct and state allows) it calls a path finding
// formula and queues an actor move event on the game 
// logic
void AIGameView::update(const sf::Time& delta_t) {
	enemies = getGameLogic()->getEnemiesListPointer();
	updateStates();
	updateSeeks();
	moveActors();
}

void AIGameView::updateStates() {
	for (GameLogic::EnemiesList::const_iterator i = enemies->begin(); i != enemies->end(); i++) {
		i->second->checkState(getGameLogic()->getShip()->getPosition());
	}
}

void AIGameView::updateSeeks() {
	const Ship* ship = getGameLogic()->getShip();
	for (GameLogic::EnemiesList::const_iterator i = enemies->begin(); i != enemies->end(); i++) {
		EnemyActor* enemy = i->second;
		
		// always checks on pursue, otherwise checks if enemy has reaches its waypoint
		// or if it has specifically asked for a new seek
		if (enemy->getState() == EnemyActor::Pursue || enemy->checkIfAtPosition(enemy->getSeek()) || enemy->getNeedSeek())  {
			switch (enemy->getState()) {
				
				// if on patrol, the actor will attemp to move to a random tile on an opposite
				// quadrant of the map
				case EnemyActor::Patrol:
					enemy->setSeek(findOppositeSeek(enemy->getPosition()));
					break;
				
				// if fleeing, the actor will try and move to a random tile opposite of the ship
				case EnemyActor::Flee:
					enemy->setSeek(findOppositeSeek(ship->getPosition()));
					break;
					
				// if pursuing, change the seek to the ships location
				case EnemyActor::Pursue:
					enemy->setSeek(ship->getPosition());
					break;
					
				// follows the enemy saved in leader based off an offset
				case EnemyActor::Follow:
					// makes the offset a bit more random by adding -1, 0, or 1
					sf::Vector2i random((int) (rand() % 2) - 1, (int) (rand() % 2) - 1);
					sf::Vector2i temp = enemy->getFollowOffset();
					temp += random;
					temp += enemy->getLeader()->getPosition();
					enemy->setSeek(temp);
					break;
			}
			enemy->setNeedSeek(false);
		}
	}
}

void AIGameView::moveActors() {
	for (GameLogic::EnemiesList::const_iterator i = enemies->begin(); i != enemies->end(); i++) {
		EnemyActor* enemy = i->second;
		// only sends move command if enough time has passed
		if (enemy->getMoveTime() > enemy->getMinMoveTime()) {
			sf::Vector2i temp = minMaxMove(enemy);
			AICmdEvent* ai_event = new AICmdEvent(enemy->getActorId(), temp);
			getGameLogic()->getEventManager()->queueEvent(ai_event);
			enemy->setMoveTime(0.0);
		}
	}
}

sf::Vector2i AIGameView::minMaxMove(EnemyActor* enemy) {
	sf::Vector2i curr = enemy->getPosition();
	sf::Vector2i prev = enemy->getPrevPos();
	sf::Vector2i seek = enemy->getSeek();
	sf::Vector2i min = prev;
	sf::Vector2i test = curr;
	int weight = enemy->getPosDifference(prev, seek);
	Map *map = getGameLogic()->getMap();
	test.x += 1;
	if (map->isValidPosition(test) && ((enemy->getPosDifference(test, seek) < weight) || min == prev)) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	test.x -= 1;
	test.y += 1;
	if (map->isValidPosition(test) && ((enemy->getPosDifference(test, seek) < weight) || min == prev)) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	test.x -= 1;
	test.y -= 1;
	if (map->isValidPosition(test) && ((enemy->getPosDifference(test, seek) < weight) || min == prev)) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	test.y -= 1;
	if (map->isValidPosition(test) && ((enemy->getPosDifference(test, seek) < weight) || min == prev)) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	return min;
}

sf::Vector2i AIGameView::findOppositeSeek(sf::Vector2i pos_checker) {
	int randMinX;
	int randMaxX;
	int randMinY;
	int randMaxY;
	Map* map = getGameLogic()->getMap();
	if (pos_checker.x <= map->get_map_size_x() / 2) {
		randMinX = map->get_map_size_x() / 2;
		randMaxX = map->get_map_size_x();
	}
	else {
		randMinX = 0;
		randMaxX = map->get_map_size_x() / 2;
	}
	if (pos_checker.y <= map->get_map_size_y() / 2) {
		randMinY = map->get_map_size_y() / 2;
		randMaxY = map->get_map_size_y();
	}
	else {
		randMinY = 0;
		randMaxY = map->get_map_size_y() / 2;
	}
	return sf::Vector2i(randMinX + (rand() % (int)(randMaxX - randMinX + 1)), randMinY + (rand() % (int)(randMaxY - randMinY + 1)));
}