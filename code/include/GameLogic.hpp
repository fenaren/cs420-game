#if !defined GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <SFML/System/Time.hpp>

#include "EventInterface.hpp"
#include "EventManager.hpp"

#include "Actor.hpp"
#include "Ship.hpp"
#include "Map.hpp"
#include "Port.hpp"

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
  
  void ShipMoveCmdEventHandler(const EventInterface& event);
  void TransactionCheckEventHandler(const EventInterface& event);
  void TransactionSuccessEventHandler(const EventInterface& event);
  void TransactionFailEventHandler(const EventInterface& event);

  EventManager* getEventManager();

private:

  typedef std::list<const Actor*> ActorList;

  EventManager event_manager;

  Ship ship;
  Port port1, port2, port3, port4;
  Map map;
};

inline EventManager* GameLogic::getEventManager()
{
  return &event_manager;
}

#endif
