#include "UITextInput.hpp"

void UITextInput::initialize(float sX, float sY, float curX, float curY, Orientation orient) {
	UIElement::initialize(sX, sY, curX, curY, orient);
	rectangle.setPosition(sf::Vector2f(posX, posY));
	rectangle.setSize(sf::Vector2f(sizeX, sizeY));
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(3);
	rectangle.setFillColor(sf::Color::Black);
}

void UITextInput::resize(float curX, float curY) {
	UIElement::resize(curX, curY);
	rectangle.setPosition(sf::Vector2f(posX, posY));
	rectangle.setSize(sf::Vector2f(sizeX, sizeY));
}

void UITextInput::draw(sf::RenderWindow* window) {
	window->draw(rectangle);
}