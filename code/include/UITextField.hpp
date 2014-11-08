#if !defined UI_TEXT_FIELD_HPP
#define UI_TEXT_FIELD_HPP

#include <SFML/Graphics.hpp>

#include "UIElement.hpp"

class UITextField : public UIElement
{
public:

  UITextField();

  virtual ~UITextField();

private:

  sf::Font font;

  sf::Text text;
};

#endif
