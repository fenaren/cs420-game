#if !defined MERCHANT_HPP
#define MERCHANT_HPP

#include "EnemyActor.hpp"

class Merchant : public EnemyActor {
	
public:
	Merchant(ActorId actor_id);
	virtual void checkState(sf::Vector2i ship_pos);
	virtual bool initialize(); 
	virtual void update(const sf::Time& delta_t);
	
private:
	const double EMPTY_TIMER = 10.0;
	double emptyTimer;
};

#endif