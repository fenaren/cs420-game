#include "UIElement.hpp"
#include <iostream>

UIElement::UIElement() {
	
}

UIElement::~UIElement() {
	
}

// should be called immediately after creation
void UIElement::initialize(float sX, float sY, float curX, float curY, Orientation orient) {
	sizeX = sX;
	sizeY = sY;
	orientation = orient;
	resize(curX, curY);
}

// reorients in screen space on a resize
void UIElement::resize(float curX, float curY) {
	switch (orientation) {
		case TopLeft:
			posX = 0;
			posY = 0;
			break;
			
		case TopRight:
			posX = curX - sizeX;
			posY = 0;
			break;
			
		case BottomLeft:
			posX = 0;
			posY = curY - sizeY;
			break;
			
		case BottomRight:
			posX = curX - sizeX;
			posY = curY - sizeY;
			break;
			
		case Center:
			posX = (curX / 2) - (sizeX / 2);
			posY = (curY / 2) - (sizeY / 2);
			break;
	}
}

void UIElement::draw(sf::RenderWindow* window) {
	
}
