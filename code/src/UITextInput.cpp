#include "UITextInput.hpp"

void UITextInput::initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient) {
	UIElement::initialize(s, curRes, orient);
	rectangle.setPosition(pos);
	rectangle.setSize(size);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(3);
	rectangle.setFillColor(sf::Color::Black);
	font.loadFromFile("Arial.ttf");
	input = ":";
	inputText.setFont(font);
	inputText.setString(input);
	dialogue = "Rum X Price Y";
	dialogueText.setFont(font);
	dialogueText.setString(dialogue);
}

void UITextInput::resize(sf::Vector2u curRes) {
	UIElement::resize(curRes);
	rectangle.setPosition(pos);
	rectangle.setSize(size);
	inputText.setPosition(pos + sf::Vector2f(0, size.y / 2));
	dialogueText.setPosition(pos);
}

void UITextInput::inputPush(char c) {
	input += c;
	inputText.setString(input);
}

void UITextInput::inputPop() {
	if (input.length() > 1) {
		input.pop_back();
		inputText.setString(input);
	}
}

int UITextInput::clearInput() {
	if (input.length() > 1) {
		int i;
		input = input.substr(1, input.length());
		sscanf(input.c_str(), "%d", &i);
		input = ":";
		inputText.setString(input);
		return i;
	}
	return -1;
}

void UITextInput::draw(sf::RenderWindow* window) {
	window->draw(rectangle);
	window->draw(inputText);
	window->draw(dialogueText);
}