#if !defined GAME_LOGIC_HPP
#define GAME_LOGIC_HPP

#include <SFML/System/Time.hpp>

#include "EventManager.hpp"

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
};

inline EventManager* GameLogic::getEventManager()
{
  return &event_manager;
}

#endif
