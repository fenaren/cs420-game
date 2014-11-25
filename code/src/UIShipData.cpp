#include <SFML/Graphics.hpp>
#include <sstream>

#include "HumanGameView.hpp"
#include "UIShipData.hpp"

UIShipData::UIShipData() :
  UIElement(),
  rum(0),
  gold(0)
{
  // Defaults
  setPosition(sf::Vector2f(0, 0));
  setColor(sf::Color::White);
  setStyle(sf::Text::Bold);
}

UIShipData::~UIShipData()
{
}

void UIShipData::initialize(sf::Vector2f s,
			    sf::Vector2u curRes,
			    Orientation  orient)
{
}

void UIShipData::update(HumanGameView* hgv)
{
  // Adjust for prettiness
  setCharacterSize(static_cast<double>(hgv->getMapTileSize()) * 0.75);

  // Grab convenience pointer to ship
  const Ship* ship = hgv->getGameLogic()->getShip();

  setRum(ship->getRum());
  setGold(ship->getGold());
  setSupply(ship->getMaxRum());

  updateText();
}

void UIShipData::resize(sf::Vector2u curRes)
{
}

void UIShipData::draw(sf::RenderWindow* window)
{
  text.draw(window);
}

void UIShipData::updateText()
{
  // Will hold the text as it is formed
  std::string updated_text;

  // Convert rum and gold into text
  std::ostringstream num_to_str;
  num_to_str << rum;
  updated_text = "Rum: " + num_to_str.str();
  
  num_to_str.str("");
  num_to_str << supply;
  updated_text += "/" + num_to_str.str();

  num_to_str.str("");
  num_to_str << gold;
  updated_text +=" Gold: " + num_to_str.str();
  updated_text += "/500";

  text.setText(updated_text);
}
