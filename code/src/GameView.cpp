#include <SFML/System/Time.hpp>

#include "GameLogic.hpp"
#include "GameView.hpp"

GameView::GameView(GameLogic* game_logic) :
  game_logic(game_logic)
{
}

GameView::~GameView()
{
}

bool GameView::initialize()
{
  return true;
}

void GameView::update(const sf::Time& delta_t)
{
  // Process all queued events
  event_manager.processEvents();
}
