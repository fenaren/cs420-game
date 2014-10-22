#include "UITextInput.hpp"

void UITextInput::initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient) {
	UIElement::initialize(s, curRes, orient);
	rectangle.setPosition(pos);
	rectangle.setSize(size);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(3);
	rectangle.setFillColor(sf::Color::Black);
}

void UITextInput::resize(sf::Vector2u curRes) {
	UIElement::resize(curRes);
	rectangle.setPosition(pos);
	rectangle.setSize(size);
}

void UITextInput::draw(sf::RenderWindow* window) {
	window->draw(rectangle);
}