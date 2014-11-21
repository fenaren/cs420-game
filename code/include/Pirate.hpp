#if !defined PIRATE_HPP
#define PIRATE_CPP

#include "EnemyActor.hpp"

class Pirate : public EnemyActor {
	
public:
	Pirate(ActorId actor_id);
	virtual void checkState(sf::Vector2i ship_pos);
};

#endif