#if !defined UI_SHIP_DATA_HPP
#define UI_SHIP_DATA_HPP

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "UITextField.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

class UIShipData : public UIElement
{
public:

  UIShipData();

  virtual ~UIShipData();

  virtual void initialize(sf::Vector2f s,
			  sf::Vector2u curRes,
			  Orientation orient);

  virtual void update(HumanGameView* hgv);

  virtual void resize(sf::Vector2u curRes);

  virtual void draw(sf::RenderWindow* window);


  void setPosition(const sf::Vector2f& position);

  void setCharacterSize(unsigned int size);

  void setGold(unsigned int gold);

  void setRum(unsigned int rum);

  void setColor(const sf::Color& color);

  void setStyle(sf::Text::Style style);

private:

  void updateText();

  // Displays ship data
  UITextField text;

  // Gold amount to be displayed
  unsigned int gold;

  // Rum amount to be displayed
  unsigned int rum;
};

inline void UIShipData::setPosition(const sf::Vector2f& position)
{
  text.setPosition(position);
}

inline void UIShipData::setCharacterSize(unsigned int size)
{
  text.setCharacterSize(size);
}

inline void UIShipData::setGold(unsigned int gold)
{
  this->gold = gold;
}

inline void UIShipData::setRum(unsigned int rum)
{
  this->rum = rum;
}

inline void UIShipData::setColor(const sf::Color& color)
{
  text.setColor(color);
}

inline void UIShipData::setStyle(sf::Text::Style style)
{
  text.setStyle(style);
}

#endif
