#include <SFML/Graphics.hpp>
#include <iostream>

#include "HumanGameView.hpp"
#include "UITextField.hpp"

UITextField::UITextField() :
  UIElement()
{
  // Load Arial by default
  loadFontFromFile("Arial.ttf");

  // Set the default font
  text.setFont(font);

  // Sets defaults for the rest of the text properties
  text.setPosition(0, 0);
  text.setCharacterSize(10);
  text.setColor(sf::Color::Black);
  text.setString("UITextField");
}

UITextField::~UITextField()
{
}

void UITextField::draw(sf::RenderWindow* window)
{
  window->draw(text);
}

void UITextField::initialize(sf::Vector2f s,
			     sf::Vector2u curRes,
			     Orientation orient)
{
}

void UITextField::update(HumanGameView* hgv)
{
}

void UITextField::resize(sf::Vector2u curRes)
{
}

bool UITextField::loadFontFromFile(const std::string& font)
{
  if (!this->font.loadFromFile(font))
  {
    std::cerr << "Couldn't load UITextField font\n";
    return false;
  }

  text.setFont(this->font);

  return true;
}
