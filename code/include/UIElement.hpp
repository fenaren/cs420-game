#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include "SFML/Graphics.hpp"

class UIElement {

	public:
		UIElement();
		~UIElement();
		
		enum Orientation {TopLeft, TopRight, BottomLeft, BottomRight, Center};
		
		virtual void initialize(float posX, float posY, float curX, float curY, Orientation orient);
		virtual void resize(float curX, float curY);
		virtual void draw(sf::RenderWindow* window);
		
	protected:
		// x and y coordinate positions for origin (top left corner)
		// note: origin is relative to default size 
		float posX;
		float posY;
		
		// size of window
		// note: size is NOT relative to default size
		float sizeX;
		float sizeY;
		
		Orientation orientation;
};

#endif