#if !defined UI_PORT_DATA_HPP
#define UI_PORT_DATA_HPP

#include <SFML/Graphics.hpp>

#include "ActorId.hpp"
#include "UIElement.hpp"
#include "UITextField.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

class UIPortData : public UIElement
{
public:

  UIPortData(ActorId actor_id);

  virtual ~UIPortData();

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

  void setName(const std::string& name);

  void setRum(unsigned int rum);

  void setGold(unsigned int gold);

private:

  // The actor this is associated with
  ActorId actor_id;

  // Text field for displaying the port's name
  UITextField name_field;

  // Text field for displaying rum amount
  UITextField rum_field;

  // Text field for displaying gold amount
  UITextField gold_field;
};

inline const sf::Vector2f& UIPortData::getPosition() const
{
  // The name field draws at the top-left of this UI element so its position is
  // the position of the whole thing
  return name_field.getPosition();
}

inline unsigned int UIPortData::getCharacterSize() const
{
  // Both fields are supposed to be set to the same character size, so just
  // return the size from one of them
  return name_field.getCharacterSize();
}

inline void UIPortData::setColor(const sf::Color& color)
{
  name_field.setColor(color);
  rum_field.setColor(color);
  gold_field.setColor(color);
}

inline void UIPortData::setName(const std::string& name)
{
  name_field.setText(name);
}

#endif
