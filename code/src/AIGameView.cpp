#include "AIGameView.hpp"

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
	updateStates();
	updateSeeks();
	moveActors();
}

void AIGameView::updateStates() {
	
}

void AIGameView::updateSeeks() {
	
}

void AIGameView::moveActors() {
	
}