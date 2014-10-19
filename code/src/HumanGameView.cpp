#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameLogic.hpp"
#include "HumanGameView.hpp"

HumanGameView::HumanGameView(GameLogic* game_logic, sf::RenderWindow* App) :
  GameView(game_logic),
  App(App)  
{
	currentResX = DEFAULT_RES_X;
	currentResY = DEFAULT_RES_Y;
	resRatioX = 1;
	resRatioY = 1;
	aspectRatio = DEFAULT_RES_Y / DEFAULT_RES_X;
}

HumanGameView::~HumanGameView()
{
}

bool HumanGameView::initialize()
{
  UITextInput *test = new UITextInput();
  test->initialize(150, 200, currentResX, currentResY, UIElement::Center);
  uiList.push_back(test);
  return true;
}

void HumanGameView::update(const sf::Time& delta_t)
{
  readInputs(delta_t);
  
  App->clear(sf::Color::Black);
  
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
			
		  // on a resize it updates all the ratios
		  case (sf::Event::Resized):
			currentResX = event.size.width;
			currentResY = event.size.height;
			resRatioX = currentResX / DEFAULT_RES_X;
			resRatioY = currentResY / DEFAULT_RES_Y;
			aspectRatio = currentResY / currentResX;
			for ( UIElement* elem : uiList ) {
				elem->resize(currentResX, currentResY);
			}
			break;
	}
  }
}
  
// draws the elements in the UI list
void HumanGameView::drawUI() {
	for ( UIElement* elem : uiList ) {
		elem->draw(App);
	}
}
