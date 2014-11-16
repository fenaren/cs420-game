#if !defined ENEMYACTOR_HPP
#define ENEMYACTOR_HPP

#include "Actor.hpp"
#include "ActorId.hpp"
#include <SFML/Graphics.hpp>

class EnemyActor : public Actor {
	
	enum State { Patrol, Pursue, Flee };
	
public:
	EnemyActor();
	EnemyActor(State state, int aggro_range, sf::Vector2i seek);
	~EnemyActor();
	
	virtual void update(const sf::Time& delta_t);
	virtual bool initialize();

	// state  getter
	State getState();
	
	// state setter
	void setState(State new_state);
	
	// seek getter
	sf::Vector2i getSeek();
	
	// seek setter
	void setSeek(sf::Vector2i new_seek);
	
	// updates state based on enemy type and ship pos
	virtual void checkState(sf::Vector2i ship_pos);
	
	// aggro range setter
	void setAggroRange(int new_aggro);
	
	// aggro range getter
	int getAggroRange();
	
private:
	int aggro_range;
	State state;
	sf::Vector2i seek;
};

#endif