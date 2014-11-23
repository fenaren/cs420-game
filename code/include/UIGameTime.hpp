#if !defined UI_GAME_TIME_HPP
#define UI_GAME_TIME_HPP

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "UITextField.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

class UIGameTime : public UIElement
{
public:

  UIGameTime();

  virtual ~UIGameTime();

  virtual void initialize(sf::Vector2f s,
                          sf::Vector2u curRes,
                          Orientation orient);

  virtual void update(HumanGameView* hgv);

  virtual void resize(sf::Vector2u curRes);

  virtual void draw(sf::RenderWindow* window);


  void setPosition(const sf::Vector2f& position);

  void setCharacterSize(unsigned int size);

  void setGameTime(double game_time);

  void setColor(const sf::Color& color);

  void setStyle(sf::Text::Style style);

private:

  void updateText();

  // Displays ship data
  UITextField text;

  // Game time to be displayed
  double game_time;
};

inline void UIGameTime::setPosition(const sf::Vector2f& position)
{
  text.setPosition(position);
}

inline void UIGameTime::setCharacterSize(unsigned int size)
{
  text.setCharacterSize(size);
}

inline void UIGameTime::setGameTime(double game_time)
{
  this->game_time = game_time;
}

inline void UIGameTime::setColor(const sf::Color& color)
{
  text.setColor(color);
}

inline void UIGameTime::setStyle(sf::Text::Style style)
{
  text.setStyle(style);
}

#endif
