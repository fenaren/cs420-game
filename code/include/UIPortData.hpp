#if !defined UI_PORT_DATA_HPP
#define UI_PORT_DATA_HPP

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


private:

  // Text field for displaying rum amount
  UITextField rum_field;

  // Text field for displaying gold amount
  UITextField gold_field;
};

#endif
