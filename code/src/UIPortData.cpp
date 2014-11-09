#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

#include "ActorId.hpp"
#include "GameLogic.hpp"
#include "HumanGameView.hpp"
#include "UIPortData.hpp"

UIPortData::UIPortData(ActorId actor_id) :
  UIElement(),
  actor_id(actor_id)
{
  // Port data displayed in white
  setColor(sf::Color::White);

  // Port data initially displayed in 10 pixel size
  setCharacterSize(10);

  // Defaults
  setName("UIPortData");
  setRum(0);
  setGold(0);

  // The name field is always bold
  name_field.setStyle(sf::Text::Bold);
}

UIPortData::~UIPortData()
{
}

void UIPortData::draw(sf::RenderWindow* window)
{
  name_field.draw(window);
  rum_field.draw(window);
  gold_field.draw(window);
}

void UIPortData::initialize(sf::Vector2f s,
			    sf::Vector2u curRes,
			    Orientation  orient)
{
}

void UIPortData::update(HumanGameView* hgv)
{
  // Grab a convenience pointer back to the port we're interested in
  const Port* port = hgv->getGameLogic()->getPortsList().at(actor_id);

  setGold(port->getRumPrice());
  setRum(port->getRum());
  setCharacterSize(hgv->getMapTileSize() / 2);  // adjust for prettiness

  // Convert port position into vector
  sf::Vector2f map_position(port->getPositionX(), port->getPositionY());

  sf::Vector2f window_position;
  hgv->mapToWindow(map_position, window_position);

  setPosition(window_position);
}

void UIPortData::resize(sf::Vector2u curRes)
{
}

void UIPortData::setPosition(const sf::Vector2f& position)
{
  // The name field is displayed on top so it should be set to this position
  name_field.setPosition(position);

  // The other fields are displayed below the name field.  Where they are
  // depends on the current character size

  // Grab current name field position and set the other fields to be below it
  sf::Vector2f new_field_position = name_field.getPosition();
  new_field_position.y += name_field.getCharacterSize();
  rum_field.setPosition(new_field_position);
  new_field_position.y += name_field.getCharacterSize();
  gold_field.setPosition(new_field_position);
}

void UIPortData::setCharacterSize(unsigned int size)
{
  // First off just set the field character sizes
  name_field.setCharacterSize(size);
  rum_field.setCharacterSize(size);
  gold_field.setCharacterSize(size);

  // Changing character means the gold field will need to be repositioned, so
  // just call setPosition to the currentl location and that will happen
  setPosition(getPosition());
}

void UIPortData::loadFontFromFile(const std::string& font)
{
  if (!name_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIPortData name font\n";
  }

  if (!rum_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIPortData rum font\n";
  }

  if (!gold_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIPortData gold font\n";
  }
}

void UIPortData::setRum(unsigned int rum)
{
  // Convert the given number into a string
  std::ostringstream num_to_str;
  num_to_str << rum;

  // Plow everything into the rum field
  rum_field.setText(num_to_str.str() + " R");
}

void UIPortData::setGold(unsigned int gold)
{
  // Convert the given number into a string
  std::ostringstream num_to_str;
  num_to_str << gold;

  // Plow everything into the rum field
  gold_field.setText(num_to_str.str() + " G");
}
