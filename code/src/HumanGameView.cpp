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
					test->resize(currentRes);
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

		default:
		{
		  // Do nothing; OSX compiler complains if nothing happens after
		  // default, so the empty brackets are required
		}
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
		ShipMoveCmdEvent* sm_event = new ShipMoveCmdEvent(sf::Vector2i(x, y));
		getGameLogic()->getEventManager()->queueEvent(sm_event);
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
	std::map<ActorId, Actor*> actors = getGameLogic()->getActorList();
	int tileSize = tempMap.get_tile_size();
	sf::Sprite ship_sprite;
	ship_sprite.setTexture(texture);
	ship_sprite.setTextureRect(sf::IntRect(0,0,25,25));
	sf::Sprite port_sprite;
	port_sprite.setTexture(texture);
	port_sprite.setTextureRect(sf::IntRect(105,0,25,25));
	for (std::map<ActorId, Actor*>::reverse_iterator i = actors.rbegin(); i != actors.rend(); i++) {
		if (i->first == 0) {
			ship_sprite.setPosition(sf::Vector2f(i->second->getPositionX() * tileSize, i->second->getPositionY() * tileSize));
			App->draw(ship_sprite);
		}
		else {
			port_sprite.setPosition(sf::Vector2f(i->second->getPositionX() * tileSize, i->second->getPositionY() * tileSize));
			App->draw(port_sprite);
		}
	}
}
  
// draws the elements in the UI list
void HumanGameView::drawUI() {
	for ( UIElement* elem : uiList ) {
		elem->draw(App);
	}
}

void HumanGameView::calculateMapWindowData()
{
  // We need to know the aspect ratio of the map (here we're assuming maps are
  // always rectangular) to calculate where the left edge of the map should
  // start
  double map_aspect_ratio =
    static_cast<double>(tempMap.get_map_size_x()) /
    static_cast<double>(tempMap.get_map_size_y());

  // Get the current size of the window
  sf::Vector2u window_size = App->getSize();

  // What's the aspect ratio of the window?
  double window_aspect_ratio =
    static_cast<double>(window_size.x) / static_cast<double>(window_size.y);


  // If the map's aspect ratio is less than the window's, then there will be
  // sidebars.  If the two aspect ratios are equal, the map will fit perfectly
  // in the window and there will be no sidebars or horizontal bars.  If the
  // map's aspect ratio is greater than the window's, there will be horizontal
  // bars.

  // For now assume the top-left map coordinate is 0,0.  This will be updated
  // later if it isn't the case
  map_tl_wcoords.x = 0;
  map_tl_wcoords.y = 0;

  // The ratio between the two aspect ratios
  double ar_ratio = map_aspect_ratio / window_aspect_ratio;

  if (ar_ratio > 1.0)
  {
    map_tl_wcoords.x = 0.0;
    map_tl_wcoords.y =
      (currentRes.y - (static_cast<double>(currentRes.y) / ar_ratio)) / 2.0;

    map_tile_size = static_cast<unsigned int>(
      static_cast<double>(window_size.x) /
      static_cast<double>(tempMap.get_map_size_x()));
  }
  else if (ar_ratio < 1.0)
  {
    map_tl_wcoords.x =
      (currentRes.x - (static_cast<double>(currentRes.x) * ar_ratio)) / 2.0;;
    map_tl_wcoords.y = 0.0;

    map_tile_size = static_cast<unsigned int>(
      static_cast<double>(window_size.y) /
      static_cast<double>(tempMap.get_map_size_y()));
  }
}

void HumanGameView::mapToWindow(const sf::Vector2u& map_coords,
				sf::Vector2u&       window_coords)
{
}
