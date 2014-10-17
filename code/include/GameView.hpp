#if !defined GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/System/Time.hpp>

#include "EventManager.hpp"
#include "GameLogic.hpp"

class GameView
{
public:

  GameView();

  ~GameView();

  /* Does everything necessary to initialize the game view.  Should run
     immediately after GameView construction. */
  virtual bool initialize(GameLogic* game_logic);

  /* Called on a per-frame basis.  Causes the GameView to do all actions
     necessary on a frame. */
  virtual void update(const sf::Time& delta_t);

  EventManager* getEventManager();

  GameLogic* getGameLogic();

private:

  EventManager event_manager;

  // Views have to be able to get at the game logic for various reasons
  GameLogic* game_logic;
};

inline EventManager* GameView::getEventManager()
{
  return &event_manager;
}

inline GameLogic* GameView::getGameLogic()
{
  return game_logic;
}

#endif
