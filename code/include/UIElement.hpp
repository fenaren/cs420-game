#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include "SFML/Graphics.hpp"

class UIElement {

	public:
		UIElement();
		~UIElement();
		
		enum Orientation {TopLeft, TopRight, BottomLeft, BottomRight, Center};
		
		virtual void initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient);
		virtual void resize(sf::Vector2u curRes);
		virtual void draw(sf::RenderWindow* window);
		
	protected:
		// x and y coordinate positions for origin (top left corner)
		// note: origin is relative to default size 
		sf::Vector2f pos;
		
		// size of window
		// note: size is NOT relative to default size
		sf::Vector2f size;
		
		Orientation orientation;
};

#endif