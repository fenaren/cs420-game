#ifndef UITEXTINPUT_HPP
#define UITEXTINPUT_HPP

#include "UIElement.hpp"

class UITextInput : public UIElement {
	
public:
	virtual void initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient);
	virtual void resize(sf::Vector2u curRes);
	virtual void draw(sf::RenderWindow* window);
	virtual void setDialogue(std::string str);
	
	void inputPush(char c);
	
	// won't pop the initial read character
	void inputPop();
	
	// returns the int so it can be passed to events
	int clearInput();
	
private:
	sf::RectangleShape rectangle;
	std::string input;
	sf::Font font;
	sf::Text inputText;
	std::string dialogue;
	sf::Text dialogueText;
};
#endif