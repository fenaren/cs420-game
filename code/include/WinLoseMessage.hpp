#if !defined WIN_LOSE_MESSAGE_HPP
#define WIN_LOSE_MESSAGE_HPP

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "UITextField.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

class WinLoseMessage : public UIElement
{
public:

  WinLoseMessage();

  virtual ~WinLoseMessage();

  virtual void initialize(sf::Vector2f s,
                          sf::Vector2u curRes,
                          Orientation orient);

  virtual void update(HumanGameView* hgv);

  virtual void resize(sf::Vector2u curRes);

  virtual void draw(sf::RenderWindow* window);


  void setPosition(const sf::Vector2f& position);

  void setCharacterSize(unsigned int size);

  void setMessage(std::string message);

  void setColor(const sf::Color& color);

  void setStyle(sf::Text::Style style);

private:

  void updateText();

  // Displays ship data
  UITextField text;

  // Win or lose message to be displayed
  std::string message;
};

inline void WinLoseMessage::setPosition(const sf::Vector2f& position)
{
  text.setPosition(position);
}

inline void WinLoseMessage::setCharacterSize(unsigned int size)
{
  text.setCharacterSize(size);
}

inline void WinLoseMessage::setMessage(std::string message)
{
  this->message = message;
}

inline void WinLoseMessage::setColor(const sf::Color& color)
{
  text.setColor(color);
}

inline void WinLoseMessage::setStyle(sf::Text::Style style)
{
  text.setStyle(style);
}

#endif
