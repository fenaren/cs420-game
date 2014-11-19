#include "AIGameView.hpp"

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
	enemies = getGameLogic()->getEnemiesList();
	updateStates();
	updateSeeks();
	moveActors();
}

void AIGameView::updateStates() {
	sf::Vector2i temp(getGameLogic()->getShip()->getPositionX(), getGameLogic()->getShip()->getPositionY());
	for (EnemiesList::iterator i = enemies.begin(); i != enemies.end(); i++) {
		i->second->checkState(temp);
	}
}

void AIGameView::updateSeeks() {
	const Ship* ship = getGameLogic()->getShip();
	for (EnemiesList::iterator i = enemies.begin(); i != enemies.end(); i++) {
		EnemyActor* enemy = i->second;
		if (enemy->checkIfAtPosition(enemy->getSeek()) || enemy->getNeedSeek()) {
			switch (enemy->getType()) {
				
				// if on patrol, the actor will attemp to move to a random tile on an opposite
				// quadrant of the map
				case EnemyActor::Patrol:
					enemy->setSeek(findOppositeSeek(sf::Vector2i(enemy->getPositionX(), enemy->getPositionY())));
					break;
				
				// if fleeing, the actor will try and move to a random tile opposite of the ship
				case EnemyActor::Flee:
					enemy->setSeek(findOppositeSeek(sf::Vector2i(ship->getPositionX(), enemy->getPositionY())));
					break;
					
				// if pursuing, constantly change the seek to the ships location
				case EnemyActor::Pursue:
					enemy->setSeek(sf::Vector2i(ship->getPositionX(), ship->getPositionY()));
					break;
					
				// follows the enemy saved in leader based off an offset
				case EnemyActor::Follow:
					// makes the offset a bit more random
					int randX = (rand() % 2) - 1;
					int randY = (rand() % 2) - 1;
					sf::Vector2i temp = enemy->getFollowOffset();
					temp.x += (enemy->getLeader()->getPositionX() + randX);
					temp.y += (enemy->getLeader()->getPositionY() + randY);
					enemy->setSeek(temp);
					break;
			}
			enemy->setNeedSeek(false);
		}
	}
}

void AIGameView::moveActors() {
	for (EnemiesList::iterator i = enemies.begin(); i != enemies.end(); i++) {
		EnemyActor* enemy = i->second;
		// only sends move command if enough time has passed
		if (enemy->getMoveTime() > enemy->getMinMoveTime()) {
			sf::Vector2i temp = minMaxMove(sf::Vector2i(enemy->getPositionX(), enemy->getPositionY()), enemy->getSeek());
			ActorMovedEvent* am_event = new ActorMovedEvent(enemy->getActorId(), temp.x, temp.y);
			getGameLogic()->getEventManager()->queueEvent(am_event);
			enemy->setMoveTime(0.0);
		}
	}
}

sf::Vector2i AIGameView::minMaxMove(sf::Vector2i start, sf::Vector2i end) {
	
}

sf::Vector2i AIGameView::findOppositeSeek(sf::Vector2i pos_checker) {
	
}