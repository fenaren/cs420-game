#if !defined ENEMYACTOR_HPP
#define ENEMYACTOR_HPP

#include "Actor.hpp"
#include "ActorId.hpp"
#include <cmath>

class EnemyActor : public Actor {
	
public:
	enum State { Patrol, Pursue, Flee, Follow, Stop };
	enum Type { Pirate, Merchant, Kraken, Tentacle };
	EnemyActor(ActorId actor_id);
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
	
	// type setter
	void setType(Type new_type);
	
	// type getter
	Type getType();
	
	// need seek setter
	void setNeedSeek(bool new_need);
	
	// need seek getter
	bool getNeedSeek();
	
	// prev pos setter
	void setPrevPos(sf::Vector2i new_prev);
	
	// follow offset getter
	sf::Vector2i getFollowOffset();
	
	// rum penalty setter
	void setRumPenalty(int new_rum);
	
	// rum penalt getter
	int getRumPenalty();
	
	// follow offset setter
	void setFollowOffset(sf::Vector2i new_offset);
	
	// prev pos getter
	sf::Vector2i getPrevPos();
	
	// leader getter
	EnemyActor* getLeader();
	
	// leader setter
	void setLeader(EnemyActor* new_leader);
	
	double getPatrolTimer();
	
	void setPatrolTimer(double new_pat_timer);
	
	double getPatrolTimerMin();
	
	double setPatrolTimerMin(double new_pat_min);
	
	// checks if given vector is within aggro range
	// aggro range represents single tiles away from
	// actor, so for example 4 range could mean 4 tiles
	// to the left or 1 tile up and 3 tiles to the left
	bool checkAggroRange(sf::Vector2i pos_checker);
	
	// Returns an int representing the difference in position
	// from this enemy actor
	int getPosDifference(sf::Vector2i first, sf::Vector2i second);
	
	// checks if this actor is at a position
	bool checkIfAtPosition(sf::Vector2i pos_checker);
	
private:
	int aggro_range;
	int rum_penalty;
	State state;
	Type type;
	sf::Vector2i seek;
	sf::Vector2i prev_pos;
	
	EnemyActor* leader;
	sf::Vector2i follow_offset;
	bool need_seek;
	
	double patrolTimerMin;
	double patrolTimer;
};

#endif