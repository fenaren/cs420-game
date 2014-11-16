#if !defined AI_GAME_VIEW_HPP
#define AI_GAME_VIEW_HPP

#include "EnemyActor.hpp"
#include "GameView.hpp"

class AIGameView : public GameView {
	
public:
	
	typedef std::map<ActorId, EnemyActor*> EnemyList;
	
	virtual bool initialize();
	virtual void update(const sf::Time& delta_t);
	
	// goes over the enemies and figures out if they need to change state
	void updateStates();
	
	// updates the enemies seek position based off their state
	void updateSeeks();
	
	// sends move commands if an actor can/wants to move
	void moveActors();
	
	// returns the vector for a min max move  based of a current position
	// and the position that the actor wishes to reach
	sf::Vector2i minMaxMove(sf::Vector2i start, sf::Vector2i end);
	
private:
	
};

#endif