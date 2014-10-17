#include <SFML/System/Time.hpp>

#include "GameLogic.hpp"
#include "GameView.hpp"

GameView::GameView()
{
}

GameView::~GameView()
{
}

bool GameView::initialize(GameLogic* game_logic)
{
  this->game_logic = game_logic;

  return true;
}

void GameView::update(const sf::Time& delta_t)
{
  // Process all queued events
  event_manager.processEvents();
}
