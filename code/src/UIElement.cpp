#include "UIElement.hpp"
#include <iostream>

UIElement::UIElement() {
	
}

UIElement::~UIElement() {
	
}

// should be called immediately after creation
void UIElement::initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient) {
	size = s;
	orientation = orient;
	resize(curRes);
}

// reorients in screen space on a resize
void UIElement::resize(sf::Vector2u curRes) {
	switch (orientation) {
		case TopLeft:
			pos.x = 0;
			pos.y = 0;
			break;
			
		case TopRight:
			pos.x = curRes.x - size.x;
			pos.y = 0;
			break;
			
		case BottomLeft:
			pos.x = 0;
			pos.y = curRes.y - size.y;
			break;
			
		case BottomRight:
			pos.x = curRes.x - size.x;
			pos.y = curRes.y - size.y;
			break;
			
		case Center:
			pos.x = (curRes.x / 2) - (size.x / 2);
			pos.y = (curRes.y / 2) - (size.y / 2);
			break;
	}
}

void UIElement::draw(sf::RenderWindow* window) {
	
}
