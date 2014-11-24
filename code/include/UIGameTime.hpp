#if !defined UI_GAME_TIME_HPP
#define UI_GAME_TIME_HPP

#include <SFML/Graphics.hpp>

#include "ActorId.hpp"
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

  virtual void draw(sf::RenderWindow* window);

  virtual void initialize(sf::Vector2f s,
			  sf::Vector2u curRes,
			  Orientation  orient);

  virtual void update(HumanGameView* hgv);

  virtual void resize(sf::Vector2u curRes);


  void setPosition(const sf::Vector2f& position);

  const sf::Vector2f& getPosition() const;

  void setCharacterSize(unsigned int size);

  unsigned int getCharacterSize() const;

  void setColor(const sf::Color& color);

  void loadFontFromFile(const std::string& font);

  void setMessage(const std::string& message);

  void setTimer(int timer);

private:

  // Text field for displaying the timer's text
  UITextField message_field;

  // Text field for displaying timer's amount
  UITextField timer_field;
};

inline const sf::Vector2f& UIGameTime::getPosition() const
{
  // The name field draws at the top-left of this UI element so its position is
  // the position of the whole thing
  return message_field.getPosition();
}

inline unsigned int UIGameTime::getCharacterSize() const
{
  // Both fields are supposed to be set to the same character size, so just
  // return the size from one of them
  return message_field.getCharacterSize();
}

inline void UIGameTime::setColor(const sf::Color& color)
{
  message_field.setColor(color);
  timer_field.setColor(color);
}

inline void UIGameTime::setMessage(const std::string& message)
{
  message_field.setText(message);
}

#endif
