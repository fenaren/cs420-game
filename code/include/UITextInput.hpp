#ifndef UITEXTINPUT_HPP
#define UITEXTINPUT_HPP

#include "UIElement.hpp"

class UITextInput : public UIElement {
	
public:
	virtual void initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient);
	virtual void resize(sf::Vector2u curRes);
	virtual void draw(sf::RenderWindow* window);
	
private:
	sf::RectangleShape rectangle;
};
#endif