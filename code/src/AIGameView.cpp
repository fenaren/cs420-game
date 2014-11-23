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
					
				case EnemyActor::Stop:
					enemy->setSeek(enemy->getPosition());
					break;
					
				// follows the enemy saved in leader based off an offset
				case EnemyActor::Follow:
					sf::Vector2i temp = enemy->getLeader()->getPosition() + enemy->getFollowOffset();
					if (!getGameLogic()->getMap()->isValidPosition(temp))
						temp = enemy->getLeader()->getPosition();
					enemy->setSeek(temp);
					break;
			}
		}
	}
}

void AIGameView::moveActors() {
	for (GameLogic::EnemiesList::const_iterator i = enemies->begin(); i != enemies->end(); i++) {
		EnemyActor* enemy = i->second;
		if (enemy->getState() != EnemyActor::Stop) {
			sf::Vector2i temp = minMaxMove(enemy);
			AICmdEvent* ai_event = new AICmdEvent(enemy->getActorId(), temp);
			getGameLogic()->getEventManager()->queueEvent(ai_event);
		}
	}
}

sf::Vector2i AIGameView::minMaxMove(EnemyActor* enemy) {
	sf::Vector2i curr = enemy->getPosition();
	sf::Vector2i prev = enemy->getPrevPos();
	sf::Vector2i seek = enemy->getSeek();
	if (curr == seek)
		return curr;
	sf::Vector2i min = prev;
	sf::Vector2i test = curr;
	int weight = 500;
	Map *map = getGameLogic()->getMap();
	// idea here is it checks the opposite of prev first to reduce chance of circles
	if (!enemy->getNeedSeek()) {
		sf::Vector2i diff = curr - prev;
		-diff;
		test = curr + diff;
		if (test != prev && map->isValidPosition(test) && enemy->getPosDifference(test, seek) < weight) {
			weight = enemy->getPosDifference(test, seek);
			min = test;
		}
	}
	test = curr;
	test.y -= 1;
	if (test != prev && map->isValidPosition(test) && enemy->getPosDifference(test, seek) < weight) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	test = curr;
	test.x -= 1;
	if (map->isValidPosition(test) && enemy->getPosDifference(test, seek) < weight && test != prev) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	test = curr;
	test.y += 1;
	if (map->isValidPosition(test) && enemy->getPosDifference(test, seek) < weight && test != prev) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	test = curr;
	test.x += 1;
	if (map->isValidPosition(test) && enemy->getPosDifference(test, seek) < weight && test != prev) {
		weight = enemy->getPosDifference(test, seek);
		min = test;
	}
	if (prev == seek)
		min = prev;
	if (min == enemy->getLeader()->getPosition())
		return curr;
	return min;
}

sf::Vector2i AIGameView::findOppositeSeek(sf::Vector2i pos_checker) {
	int randMinX;
	int randMaxX;
	int randMinY;
	int randMaxY;
	int adjX;
	int adjY;
	Map* map = getGameLogic()->getMap();
	if (pos_checker.x < map->get_map_size_x() / 2) {
		randMinX = map->get_map_size_x() / 2;
		randMaxX = map->get_map_size_x() - 1;
		adjX = 1;
	}
	else {
		randMinX = 0;
		randMaxX = map->get_map_size_x() / 2;
		adjX = -1;
	}
	if (pos_checker.y < map->get_map_size_y() / 2) {
		randMinY = map->get_map_size_y() / 2;
		randMaxY = map->get_map_size_y() - 1;
		adjY = 1;
	}
	else {
		randMinY = 0;
		randMaxY = map->get_map_size_y() / 2;
		adjY = -1;
	}
	int x = randMinX + (rand() % (int)(randMaxX - randMinX + 1));
	int y = randMinY + (rand() % (int)(randMaxY - randMinY + 1));
	
	// moves the point towards center if not at a valid position
	while (!map->isValidPosition(sf::Vector2i(x, y))) {
		x += adjX;
		y += adjY;
	}
	return sf::Vector2i(x, y);
}