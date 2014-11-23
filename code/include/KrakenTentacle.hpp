#if !defined KRAKEN_TENTACLE_HPP
#define KRAKEN_TENTACLE_HPP

#include "EnemyActor.hpp"

class KrakenTentacle : public EnemyActor {
	
public:
	KrakenTentacle(ActorId actor_id);
	virtual void checkState(sf::Vector2i ship_pos);
	virtual bool initialize(); 
	virtual void update(const sf::Time& delta_t);
	
private:
};

#endif