#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameLogic.hpp"
#include "HumanGameView.hpp"

HumanGameView::HumanGameView(GameLogic* game_logic, sf::RenderWindow* App) :
  GameView(game_logic),
  App(App)  
{
	if (!texture.loadFromFile("./data/sprites.png")) {
		std::cout << "ERROR TEXTURE" << std::endl;
	}
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
  if (!tempMap.createMap("./data/second_map.txt")) {
	std::cout << "ERROR MAP" << std::endl;
  }
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
		y--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		y++;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x++;
	if (x != 0 || y != 0) {
		// send shipmovecmdevent here
	}
  }
}

// draws the map
void HumanGameView::drawMap() {
	int x_position = 0;
	int y_position = 0;
	// these things never change as of right now so they could be created as
	// members of the class...
	int tile_size = tempMap.get_tile_size();
	int map_size_x = tempMap.get_map_size_x();
	int map_size_y = tempMap.get_map_size_y();
	sf::Sprite land_sprite;
	sf::Sprite water_sprite;
	land_sprite.setTexture(texture);
	water_sprite.setTexture(texture);
	land_sprite.setTextureRect(sf::IntRect(106,50,25,25));
	water_sprite.setTextureRect(sf::IntRect(106,25,25,25));
	
	for (int y = 0; y < map_size_y; y++) {
        	for (int x = 0; x < map_size_x; x++) {
			if (tempMap.getTerrain(x,y) == 1) {
                		land_sprite.setPosition(sf::Vector2f(x_position, y_position));
                		App->draw(land_sprite);
            		}
            		else {
                		water_sprite.setPosition(sf::Vector2f(x_position, y_position));
                		App->draw(water_sprite);
            		}
            		x_position += tile_size;
        	}
        	x_position = 0;
        	y_position += tile_size;
    	}
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
