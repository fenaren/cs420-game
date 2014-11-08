#include <SFML/Graphics.hpp>
#include <iostream>

#include "UIPortData.hpp"

UIPortData::UIPortData() :
  UIElement()
{
  // Port data displayed in white
  setColor(sf::Color::White);

  // Port data initially displayed in 10 pixel size
  setCharacterSize(10);
}

UIPortData::~UIPortData()
{
}

void UIPortData::draw(sf::RenderWindow* window)
{
  rum_field.draw(window);
  gold_field.draw(window);
}

void UIPortData::initialize(sf::Vector2f s,
			    sf::Vector2u curRes,
			    Orientation  orient)
{
}

void UIPortData::resize(sf::Vector2u curRes)
{
}


void UIPortData::setPosition(const sf::Vector2f& position)
{
  // The rum field is displayed on top so it should be set to this position
  rum_field.setPosition(position);

  // The gold field is displayed below the rum field.  Where this is depends on
  // the current character size.

  // Grab current rum field position and set the gold field to be below it
  sf::Vector2f new_gold_field_position = rum_field.getPosition();
  new_gold_field_position.y += rum_field.getCharacterSize();
  gold_field.setPosition(new_gold_field_position);
}

void UIPortData::setCharacterSize(unsigned int size)
{
  // First off just set the field character sizes
  rum_field.setCharacterSize(size);
  gold_field.setCharacterSize(size);

  // Changing character means the gold field will need to be repositioned, so
  // just call setPosition to the currently location and that will happen
  setPosition(getPosition());
}

void UIPortData::loadFontFromFile(const std::string& font)
{
  if (!rum_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIPortData rum font\n";
  }

  if (!gold_field.loadFontFromFile(font))
  {
    std::cerr << "Couldn't load UIPortData gold font\n";
  }
}
