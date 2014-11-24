#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "ActorId.hpp"
#include "GameLogic.hpp"
#include "HumanGameView.hpp"
#include "UIGameTime.hpp"

UIGameTime::UIGameTime() :
  UIElement()
{
  // timer data displayed in black
  setColor(sf::Color::White);

  // timer data initially displayed in 10 pixel size
  setCharacterSize(10);

  // Defaults
  setMessage("Time Until Loan Shark: ");
  setTimer(0.0);

  // both fields are always bold
  message_field.setStyle(sf::Text::Bold);
  timer_field.setStyle(sf::Text::Bold);
}

UIGameTime::~UIGameTime()
{
}

void UIGameTime::draw(sf::RenderWindow* window)
{
  message_field.draw(window);
  timer_field.draw(window);
}

void UIGameTime::initialize(sf::Vector2f s,
			    sf::Vector2u curRes,
			    Orientation  orient)
{
}

void UIGameTime::update(HumanGameView* hgv)
{
  // Grab a convenience pointer back to the port we're interested in
  setTimer(hgv->getGameLogic()->getGameTime());
  setCharacterSize(hgv->getMapTileSize() / 1.5);

  // Convert port position into vector
  sf::Vector2f map_position(22, 0);

  sf::Vector2f window_position;
  hgv->mapToWindow(map_position, window_position);

  setPosition(window_position);
}

void UIGameTime::resize(sf::Vector2u curRes)
{
}

void UIGameTime::setPosition(const sf::Vector2f& position)
{
  message_field.setPosition(position);
  
  sf::Vector2f new_field_position = message_field.getPosition();
  new_field_position.x += 12 * getCharacterSize();
  timer_field.setPosition(new_field_position);
}

void UIGameTime::setCharacterSize(unsigned int size)
{
  // First off just set the field character sizes
  message_field.setCharacterSize(size);
  timer_field.setCharacterSize(size);

  setPosition(getPosition());
}

void UIGameTime::loadFontFromFile(const std::string& font)
{
  if (!message_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIGameTime message font\n";
  }

  if (!timer_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIGameTime timer font\n";
  }
}

void UIGameTime::setTimer(int timer)
{
  // Convert the given number into a string
  std::ostringstream num_to_str;
  num_to_str << timer / 60;
  num_to_str << ":";
  num_to_str << timer % 60;

  timer_field.setText(num_to_str.str());
}
