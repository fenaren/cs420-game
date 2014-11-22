#if !defined GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <SFML/System/Time.hpp>
#include <map>

#include "EventInterface.hpp"
#include "EventManager.hpp"

#include "Actor.hpp"
#include "ActorId.hpp"
#include "Ship.hpp"
#include "Map.hpp"
#include "Port.hpp"
#include "EnemyActor.hpp"
#include "Pirate.hpp"

class GameLogic
{
public:

  GameLogic();

  ~GameLogic();


  // Define a couple types to make working with our containers easier
  typedef std::map<ActorId, Actor*> ActorList;
  typedef std::map<ActorId, Port*>  PortsList;
  typedef std::map<ActorId, EnemyActor*>  EnemiesList;


  /* Does everything necessary to initialize the game logic.  Should run
     immediately after GameLogic construction. */
  bool initialize();

  /* Called on a per-frame basis.  Causes the GameLogic to do all actions
     necessary on a frame. */
  void update(const sf::Time& delta_t);

  // Returns a pointer to the event manager.  Allows things external to the game
  // logic to queue events in the game logic.
  EventManager* getEventManager();

  const ActorList& getActorList() const;

  const PortsList& getPortsList() const;
  
  const EnemiesList* getEnemiesListPointer() const;

  const Ship* getShip() const;
  
  Map* getMap();


  // EVENT HANDLERS

  // Handles the ShipMoveCmdEvent.  This should cause the game logic to act as
  // if the user command the ship to move.  Move ship, collide with terrain,
  // start transactions, etc.
  void ShipMoveCmdEventHandler(const EventInterface& event);

  // Handles the TransactionCheckEvent.  This takes transaction request data
  // from the game view and applies game mechanics to complete the transaction.
  // Transactions can succeed or fail depending on the transaction parameters,
  // and this will queue the appropriate events in those cases.
  void TransactionCheckEventHandler(const EventInterface& event);
  
  // Handles an ActorMoveEvent.  Makes sure based off map that it is a valid move
  // then moves the actor to that location
  void AICmdEventHandler(const EventInterface& event);

private:

  // Containers for actors and other things
  ActorList actors;
  PortsList ports;
  EnemiesList enemies;

  // The game logic's event manager
  EventManager event_manager;

  // Convenience pointer to the player' ship
  Ship* ship;

  // The game map.  Contains terrain data.
  Map map;
};

inline EventManager* GameLogic::getEventManager()
{
  return &event_manager;
}

inline const GameLogic::ActorList& GameLogic::getActorList() const
{
  return actors;
}

inline const GameLogic::PortsList& GameLogic::getPortsList() const
{
  return ports;
}

inline  const GameLogic::EnemiesList* GameLogic::getEnemiesListPointer() const 
{
	return &enemies;
}

inline const Ship* GameLogic::getShip() const
{
  return ship;
}

inline  Map* GameLogic::getMap() {
	return &map;
}

#endif
