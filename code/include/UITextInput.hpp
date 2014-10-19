#ifndef UITEXTINPUT_HPP
#define UITEXTINPUT_HPP

#include "UIElement.hpp"

class UITextInput : public UIElement {
	
public:
	void initialize(float posX, float posY, float curX, float curY, Orientation orient);
	void resize(float curX, float curY);
	void draw(sf::RenderWindow* window);
	
private:
	sf::RectangleShape rectangle;
};
#endif