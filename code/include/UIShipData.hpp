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


  void setGold(unsigned int gold);

  void setRum(unsigned int rum);

private:

  void updateText();

  // Displays ship data
  UITextField text;

  // Gold amount to be displayed
  unsigned int gold;

  // Rum amount to be displayed
  unsigned int rum;
};

inline void UIShipData::setGold(unsigned int gold)
{
  this->gold = gold;
}

inline void UIShipData::setRum(unsigned int rum)
{
  this->rum = rum;
}

#endif
