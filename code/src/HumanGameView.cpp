#include <iostream>
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
	lastShipX = 10;
	lastShipY = 11;
	shipSpriteY = 0;
}

HumanGameView::~HumanGameView()
{
}

bool HumanGameView::initialize()
{
  test = new UITextInput();
  test->initialize(sf::Vector2f(150, 100), currentRes, UIElement::Center);
  if (!tempMap.createMap("./data/second_map.txt")) {
	std::cout << "ERROR MAP" << std::endl;
  }
  getGameLogic()->getEventManager()->addDelegate(
    EventDelegate(std::bind(&HumanGameView::transactionFailEventHandler,
			    this,
			    std::placeholders::_1)),
    TransactionFailEvent::event_type);
	getGameLogic()->getEventManager()->addDelegate(
    EventDelegate(std::bind(&HumanGameView::transactionSuccessEventHandler,
			    this,
			    std::placeholders::_1)),
    TransactionSuccessEvent::event_type);
	getGameLogic()->getEventManager()->addDelegate(
    EventDelegate(std::bind(&HumanGameView::transactionStartEventHandler,
			    this,
			    std::placeholders::_1)),
    TransactionStartEvent::event_type);
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
			
			// if an input menu is open returns the int and clears it
			if (event.key.code == sf::Keyboard::Return) {
				if (menuOpen) {
					double tempdouble = test->clearInput();
					if (tempdouble >= 0) {
						TransactionCheckEvent* tc_event = new TransactionCheckEvent(tc_shipid, tc_portid, tc_shipgold, tc_shiprum, tc_portrum, tempdouble);
						getGameLogic()->getEventManager()->queueEvent(tc_event);
					}
				}
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
	int tileSize = tempMap.get_tile_size();
	
	sf::Sprite port_sprite;
	port_sprite.setTexture(texture);
	port_sprite.setTextureRect(sf::IntRect(105,0,25,25));
	std::map<ActorId, Port*> ports = getGameLogic()->getPortsList();
	for (std::map<ActorId, Port*>::iterator i = ports.begin(); i != ports.end(); i++) {
		if(i->second->isBuyPort()){
			port_sprite.setColor(sf::Color::Red);
		}
		else {
			port_sprite.setColor(sf::Color::Yellow);
		}
		port_sprite.setPosition(sf::Vector2f(i->second->getPositionX() * tileSize, i->second->getPositionY() * tileSize));
		App->draw(port_sprite);
	}

	sf::Sprite ship_sprite;
	ship_sprite.setTexture(texture);
	const Ship* ship = getGameLogic()->getShip();

	// ship moved left
	if (lastShipX > ship->getPositionX()) {
		shipSpriteY = 25;
	}
	// ship moved right
	else if (lastShipX < ship->getPositionX()) {
		shipSpriteY = 50;
	}
	// ship moved up
	else if (lastShipY > ship->getPositionY()) {
		shipSpriteY = 75;
	}
	// ship moved down
	else if (lastShipY < ship->getPositionY()) {
		shipSpriteY = 0;
	}

	ship_sprite.setTextureRect(sf::IntRect(0,shipSpriteY,25,25));
	ship_sprite.setPosition(sf::Vector2f(ship->getPositionX() * tileSize, ship->getPositionY() * tileSize));
	App->draw(ship_sprite);

	lastShipX = ship->getPositionX();
	lastShipY = ship->getPositionY();
}
  
// draws the elements in the UI list
void HumanGameView::drawUI() {
	for ( UIElement* elem : uiList ) {
		elem->draw(App);
	}
}

// handles transaction fails
void HumanGameView::transactionFailEventHandler(const EventInterface& event) {
	std::ostringstream oss;
	oss << "Incorrect Amount!\nSupply: " << tc_portrum << "\nPrice: " << (11 - tc_portrum);
	test->setDialogue(oss.str());
}

// handles transaction successes
void HumanGameView::transactionSuccessEventHandler(const EventInterface& event) {
	std::vector<UIElement*>::iterator position = std::find(uiList.begin(), uiList.end(), test);
	if (position != uiList.end())
		uiList.erase(position);
	menuOpen = false;
}

// handles transaction start
void HumanGameView::transactionStartEventHandler(const EventInterface& event) {
	if (!menuOpen) {
		test->resize(currentRes);
		uiList.push_back(test);
		menuOpen = true;
	}
	const TransactionStartEvent* ts_event =
		dynamic_cast<const TransactionStartEvent*>(&event);
	tc_shipid = ts_event->getShipId();
    tc_portid = ts_event->getPortId();
    tc_shipgold = ts_event->getShipGold();
    tc_shiprum = ts_event->getShipRum();
    tc_portrum = ts_event->getPortRum();
	std::ostringstream oss;
	oss << "Supply: " << tc_portrum << "\nPrice: " << (11 - tc_portrum);
	test->setDialogue(oss.str());
}
