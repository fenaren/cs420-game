#include <SFML/System/Time.hpp>

#include "GameLogic.hpp"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

bool GameLogic::initialize()
{
  return true;
}

void GameLogic::update(const sf::Time& delta_t)
{
  // Trigger all queued events
  event_manager.processEvents();
}
