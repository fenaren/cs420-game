#ifndef UITEXTINPUT_HPP
#define UITEXTINPUT_HPP

#include "UIElement.hpp"

// Forward declaration of HumanGameView.  This is used instead of including
// HumanGameView because including HumanGameView isn't necessary (only pointers
// to HumanGameView are present here) and because including it can cause a
// "circular include" type situation ...
class HumanGameView;

class UITextInput : public UIElement {
	
public:
	virtual void initialize(sf::Vector2f s, sf::Vector2u curRes, Orientation orient);
        virtual void update(const HumanGameView* hgv);
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
