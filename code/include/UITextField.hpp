#if !defined UI_TEXT_FIELD_HPP
#define UI_TEXT_FIELD_HPP

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"

// This class represents a simple text field.
class UITextField : public UIElement
{
public:

  UITextField();

  virtual ~UITextField();

  virtual void draw(sf::RenderWindow* window);

  virtual void initialize(sf::Vector2f s,
			  sf::Vector2u curRes,
			  Orientation  orient);

  virtual void resize(sf::Vector2u curRes);


  void setPosition(const sf::Vector2f& position);

  const sf::Vector2f& getPosition() const;

  void setCharacterSize(unsigned int size);

  unsigned int getCharacterSize() const;

  void setText(const std::string& text);

  void setColor(const sf::Color& color);

  bool loadFontFromFile(const std::string& font);

private:

  // The font the text in this text field will be drawn in
  sf::Font font;

  // The actual text of concern for this text field
  sf::Text text;
};

inline void UITextField::setPosition(const sf::Vector2f& position)
{
  text.setPosition(position);
}

inline const sf::Vector2f& UITextField::getPosition() const
{
  return text.getPosition();
}

inline void UITextField::setCharacterSize(unsigned int size)
{
  text.setCharacterSize(size);
}

inline unsigned int UITextField::getCharacterSize() const
{
  return text.getCharacterSize();
}

inline void UITextField::setText(const std::string& text)
{
  this->text.setString(text);
}

inline void UITextField::setColor(const sf::Color& color)
{
  text.setColor(color);
}

#endif
