#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameLogic.hpp"
#include "HumanGameView.hpp"

HumanGameView::HumanGameView(GameLogic* game_logic, sf::RenderWindow* App) :
  GameView(game_logic),
  App(App)  
{
	currentRes = DEFAULT_RES;
	resRatio = sf::Vector2f(1, 1);
	aspectRatio = DEFAULT_RES.x / DEFAULT_RES.y;
}

HumanGameView::~HumanGameView()
{
}

bool HumanGameView::initialize()
{
  test = new UITextInput();
  test->initialize(sf::Vector2f(150, 100), currentRes, UIElement::Center);
  //uiList.push_back(test);
  tempMap.createMap("second_map.txt");
  App->setView(sf::View(sf::FloatRect(0, 0, currentRes.x, currentRes.y)));
  return true;
}

void HumanGameView::update(const sf::Time& delta_t)
{
  readInputs(delta_t);
  
  App->clear(sf::Color::Black);
  
  drawMap();
  drawActors();
  drawUI();
  
  // Can use App to draw in the game window
  
  App->display();
  
}

// reads the inputs from the window and act on them accordingly
void HumanGameView::readInputs(const sf::Time& delta_t) {
	sf::Event event;
	while(App->pollEvent(event)) {
		switch (event.type) {
			
		  // closes window
		  case sf::Event::Closed:
			App->close();
			break;
			
		  // on a resize it updates all the ratios and makes sure
		  // that menu elements are properly oriented
		  case (sf::Event::Resized):
		    currentRes = sf::Vector2u(event.size.width, event.size.height);
			resRatio.x = currentRes.x / DEFAULT_RES.x;
			resRatio.y = currentRes.y / DEFAULT_RES.y;
			aspectRatio = currentRes.y / currentRes.x;
			for ( UIElement* elem : uiList ) {
				elem->resize(currentRes);
			}
			App->setView(sf::View(sf::FloatRect(0, 0, currentRes.x, currentRes.y)));
			break;
			
		  // handles text input
		  case (sf::Event::TextEntered):
		    if (menuOpen) {
				if (event.text.unicode >= 48 && event.text.unicode <= 57) {
					test->inputPush(event.text.unicode);
				}
				// handles backspace
				if (event.text.unicode == 8) 
					test->inputPop();
			}
		    break;
			
		  // this code will actually react to transaction request event in the future
		  case (sf::Event::KeyPressed):
			if (event.key.code == sf::Keyboard::Space) {
				if (!menuOpen) {
					uiList.push_back(test);
					menuOpen = true;
				}
				else {
					std::vector<UIElement*>::iterator position = std::find(uiList.begin(), uiList.end(), test);
					if (position != uiList.end())
						uiList.erase(position);
					menuOpen = false;
				}
			}
			// if an input menu is open returns the int and clears it
			if (event.key.code == sf::Keyboard::Return) {
				if (menuOpen) 
					test->clearInput();
			}
			break;
	}
  }
  // handles ship movement;  note: it's not in the normal SFML event manager
  // because held keys are handled different in SFML than pressed keys
  if (!menuOpen) {
	int x = 0;
	int y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
		y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x++;
	if (x != 0 || y != 0) {
		// send shipmovecmdevent here
	}
  }
}

// draws the map
void HumanGameView::drawMap() {
	tempMap.drawMap(App);
}

// draws the actors
void HumanGameView::drawActors() {
	
}
  
// draws the elements in the UI list
void HumanGameView::drawUI() {
	for ( UIElement* elem : uiList ) {
		elem->draw(App);
	}
}
