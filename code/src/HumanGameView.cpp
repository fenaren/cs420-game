#include <SFML/Graphics.hpp>

#include "GameLogic.hpp"
#include "HumanGameView.hpp"

HumanGameView::HumanGameView(GameLogic* game_logic, sf::RenderWindow* App) :
  GameView(game_logic),
  App(App)  
{
}

HumanGameView::~HumanGameView()
{
}

bool HumanGameView::initialize()
{
  GameView::initialize();

  return true;
}

void HumanGameView::update(const sf::Time& delta_t)
{
  GameView::update(delta_t);

  // Can use App to draw in the game window
}
