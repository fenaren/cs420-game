#include <SFML/Graphics.hpp>
#include <sstream>

#include "HumanGameView.hpp"
#include "UIGameTime.hpp"

UIGameTime::UIGameTime() :
  UIElement()
{
  // Defaults
  setPosition(sf::Vector2f(400, 0));
  setColor(sf::Color::White);
  setStyle(sf::Text::Bold);
}

UIGameTime::~UIGameTime()
{
}

void UIGameTime::initialize(sf::Vector2f s,
                            sf::Vector2u curRes,
                            Orientation  orient)
{
}

void UIGameTime::update(HumanGameView* hgv)
{
  // Adjust for prettiness
  setCharacterSize(static_cast<double>(hgv->getMapTileSize()) * 0.75);

  setGameTime(hgv->getGameLogic()->getGameTime());

  updateText();
}

void UIGameTime::resize(sf::Vector2u curRes)
{
}

void UIGameTime::draw(sf::RenderWindow* window)
{
  text.draw(window);
}

void UIGameTime::updateText()
{
  // Will hold the text as it is formed
  std::string updated_text;

  // Convert game time into minutes and seconds
  unsigned int minutes = (300 - game_time) / 60;
  unsigned int seconds = (int) (300 - game_time) % 60;

  // Convert game time into text
  std::ostringstream min_to_str;
  min_to_str << minutes;
  std::ostringstream sec_to_str;
  sec_to_str << seconds;
  if (seconds < 10) {
    updated_text = "Time remaining " + min_to_str.str() + ":0" + sec_to_str.str();
  }
  else {
    updated_text = "Time remaining " + min_to_str.str() + ":" + sec_to_str.str();
  }
  
  text.setText(updated_text);
}
