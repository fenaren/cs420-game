#include <SFML/Graphics.hpp>
#include <sstream>

#include "HumanGameView.hpp"
#include "WinLoseMessage.hpp"

WinLoseMessage::WinLoseMessage() :
  UIElement()
{
  // Defaults
  setPosition(sf::Vector2f(400, 300));
  setColor(sf::Color::Black);
  setStyle(sf::Text::Bold);
}

WinLoseMessage::~WinLoseMessage()
{
}

void WinLoseMessage::initialize(sf::Vector2f s,
                            sf::Vector2u curRes,
                            Orientation  orient)
{
}

void WinLoseMessage::update(HumanGameView* hgv)
{
  // Adjust for prettiness
  setCharacterSize(static_cast<double>(hgv->getMapTileSize()) * 0.75);

  message = hgv->getGameState();

  updateText();
}

void WinLoseMessage::resize(sf::Vector2u curRes)
{
}

void WinLoseMessage::draw(sf::RenderWindow* window)
{
  text.draw(window);
}

void WinLoseMessage::updateText()
{
  // Will hold the text as it is formed
  std::string updated_text = message;

  text.setText(updated_text);
}
