#if !defined GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <SFML/System/Time.hpp>

#include "EventManager.hpp"
#include "EventDelegate.hpp"

#include "Actor.hpp"
#include "Ship.hpp"
#include "Map.hpp"
#include "Port.hpp"

#include "ActorMovedEvent.hpp"
#include "ShipMoveCmdEvent.hpp"
#include "TransactionCheckEvent.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionSuccessEvent.hpp"
#include "TransactionStartEvent.hpp"

class GameLogic
{
public:

  GameLogic();

  ~GameLogic();

  /* Does everything necessary to initialize the game logic.  Should run
     immediately after GameLogic construction. */
  bool initialize();

  /* Called on a per-frame basis.  Causes the GameLogic to do all actions
     necessary on a frame. */
  void update(const sf::Time& delta_t);

  EventManager* getEventManager();

private:

  EventManager event_manager;
  typedef std::list<const Actor*> ActorList;
  Ship ship;
  Port port1, port2, port3, port4;
};

inline EventManager* GameLogic::getEventManager()
{
  return &event_manager;
}

#endif
