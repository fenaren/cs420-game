#if !defined UI_PORT_DATA_HPP
#define UI_PORT_DATA_HPP

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"
#include "UITextField.hpp"

class UIPortData : public UIElement
{
public:

  UIPortData();

  virtual ~UIPortData();

  virtual void draw(sf::RenderWindow* window);

  virtual void initialize(sf::Vector2f s,
			  sf::Vector2u curRes,
			  Orientation  orient);

  virtual void resize(sf::Vector2u curRes);


  void setPosition(const sf::Vector2f& position);

  const sf::Vector2f& getPosition() const;

  void setCharacterSize(unsigned int size);

  unsigned int getCharacterSize() const;

  void setColor(const sf::Color& color);

  void loadFontFromFile(const std::string& font);

  void setRum(unsigned int rum);

  void setGold(unsigned int gold);

private:

  // Text field for displaying rum amount
  UITextField rum_field;

  // Text field for displaying gold amount
  UITextField gold_field;
};

inline const sf::Vector2f& UIPortData::getPosition() const
{
  // The rum field draws at the top-left of this UI element so its position is
  // the position of the whole thing
  return rum_field.getPosition();
}

inline unsigned int UIPortData::getCharacterSize() const
{
  // Both fields are supposed to be set to the same character size, so just
  // return the size from one of them
  return rum_field.getCharacterSize();
}

inline void UIPortData::setColor(const sf::Color& color)
{
  rum_field.setColor(color);
  gold_field.setColor(color);
}

#endif
