#if !defined KRAKEN_HEAD_HPP
#define KRAKEN_HEAD_HPP

#include "EnemyActor.hpp"

class KrakenHead : public EnemyActor {
	
public:
	KrakenHead(ActorId actor_id);
	virtual void checkState(sf::Vector2i ship_pos);
	virtual bool initialize(); 
	virtual void update(const sf::Time& delta_t);
	
private:
};

#endif