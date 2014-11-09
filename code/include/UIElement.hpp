#ifndef UIELEMENT_HPP
#define UIELEMENT_HPP

#include "SFML/Graphics.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

class UIElement {

	public:
		UIElement();
		virtual ~UIElement();
		
		enum Orientation {TopLeft, TopRight, BottomLeft, BottomRight, Center};
		
		virtual void initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient);
                virtual void update(HumanGameView* hgv);
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
