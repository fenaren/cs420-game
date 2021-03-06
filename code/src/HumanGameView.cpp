#include <iostream>

#include "GameLostEvent.hpp"
#include "GameRestartEvent.hpp"
#include "GameWonEvent.hpp"
#include "HumanGameView.hpp"
#include "Sound.hpp"
#include "TransactionCancelEvent.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionStartEvent.hpp"
#include "TransactionSuccessEvent.hpp"
#include "UIGameTime.hpp"
#include "UITextField.hpp"
#include "UIShipData.hpp"

HumanGameView::HumanGameView(GameLogic* game_logic, sf::RenderWindow* App) :
  GameView(game_logic),
  map_tl_wcoords(0, 0),
  map_tile_size(0),
  App(App),
  tc_shipid(0),
  tc_portid(0),
  tc_shipgold(0),
  tc_shiprum(0),
  tc_portrum(0),
  tc_rum_price(0),
  sound(game_logic)
{
	if (!texture.loadFromFile("./data/sprites.png")) {
		std::cout << "ERROR TEXTURE" << std::endl;
	}
	if (!start_screen.loadFromFile("./data/title_screen.png")) {
		std::cout << "ERROR START_SCREEN" << std::endl;
	}
	if (!lose_screen.loadFromFile("./data/lose_screen.png")) {
		std::cout << "ERROR LOSE_SCREEN" << std::endl;
	}
	if (!win_screen.loadFromFile("./data/win_screen.png")) {
		std::cout << "ERROR WIN_SCREEN" << std::endl;
	}
	if (!story_screen.loadFromFile("./data/story_screen.png")) {
		std::cout << "ERROR STORY_SCREEN" << std::endl;
	}
	if (!actors_screen.loadFromFile("./data/actor_screen.png")) {
		std::cout << "ERROR ACTORS_SCREEN" << std::endl;
	}
	if (!instructions_screen.loadFromFile("./data/instructions_screen.png")) {
		std::cout << "ERROR INSTRUCTIONS_SCREEN" << std::endl;
	}
	currentRes = DEFAULT_RES;
	resRatio = sf::Vector2f(1, 1);
	aspectRatio = DEFAULT_RES.x / DEFAULT_RES.y;
	lastShipX = 10;
	lastShipY = 12;
	shipSpriteY = 0;
	game_state = "START_SCREEN";
	
}

HumanGameView::~HumanGameView()
{
  // If test is on the uiList, find it and remove it from the list before
  // deleting it
  std::vector<UIElement*>::iterator position =
    std::find(uiList.begin(), uiList.end(), test);

  if (position != uiList.end())
  {
    uiList.erase(position);
  }

  delete test;
  test = 0;

  // Delete all the UI elements
  for (std::vector<UIElement*>::iterator i = uiList.begin();
       i != uiList.end();
       i++)
  {
    delete *i;
    *i = 0;
  }
}

bool HumanGameView::initialize()
{
  test = new UITextInput();

  // Sized such that all transaction failure text fits within it
  test->initialize(sf::Vector2f(350, 100), currentRes, UIElement::Center);
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
    EventDelegate(std::bind(&HumanGameView::transactionCancelEventHandler,
			    this,
			    std::placeholders::_1)),
    TransactionCancelEvent::event_type);


  getGameLogic()->getEventManager()->addDelegate(
    EventDelegate(std::bind(&HumanGameView::transactionStartEventHandler,
			    this,
			    std::placeholders::_1)),
    TransactionStartEvent::event_type);

  getGameLogic()->getEventManager()->addDelegate(
    EventDelegate(std::bind(&HumanGameView::gameLostEventHandler,
			    this,
			    std::placeholders::_1)),
    GameLostEvent::event_type);

  getGameLogic()->getEventManager()->addDelegate(
    EventDelegate(std::bind(&HumanGameView::gameWonEventHandler,
			    this,
			    std::placeholders::_1)),
    GameWonEvent::event_type);

  // Push the UI ship data element onto the element list
  uiList.push_back(new UIShipData());

  // Push the UI game time element onto the element list
  uiList.push_back(new UIGameTime());

  // Grab a shortcut to the ports list
  const GameLogic::PortsList* ports_list = &getGameLogic()->getPortsList();

  // Set up text fields for all the ports, their data will be displayed in these
  for (GameLogic::PortsList::const_iterator i = ports_list->begin();
       i != ports_list->end();
       i++)
  {
    // Make a new UIPortData for this port
    UIPortData* new_ui_port_data = new UIPortData(i->first);

    // Set all the port names here, they're not going to change during runtime
    new_ui_port_data->setName(i->second->getName());

    // Add the port data to the UI list
    uiList.push_back(new_ui_port_data);
  }
  sound.initialize();
  sound.playTheme();
  return true;
}

void HumanGameView::update(const sf::Time& delta_t)
{
  readInputs(delta_t);
  
  App->clear(sf::Color::Black);

  calculateMapWindowData();

  // each sprite is 25x25
  spriteScale = map_tile_size / 25.0;

  drawMap();
  drawActors();

  updateUI();
  drawUI();

  drawScreen();

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
		    if (menuOpen)
		    {
		      // if an input menu is open returns the int and clears it
		      if (event.key.code == sf::Keyboard::Return)
		      {
			double tempdouble = test->clearInput();
			if (tempdouble >= 0)
			{
			  TransactionCheckEvent* tc_event =
			    new TransactionCheckEvent(tc_shipid,
						      tc_portid,
						      tc_shipgold,
						      tc_shiprum,
						      tc_portrum,
						      tempdouble);

			  getGameLogic()->getEventManager()->queueEvent(tc_event);
			}
		      }
		      // Did the user press Escape?
		      else if (event.key.code == sf::Keyboard::Escape)
		      {
			// The user wants to cancel the transaction, so queue up
			// the appropriate event with cancel set to true
			TransactionCheckEvent* tc_event =
			  new TransactionCheckEvent(true);

			getGameLogic()->getEventManager()->queueEvent(tc_event);
		      }
		    }
		    else if ((event.key.code == sf::Keyboard::Space) 
			&& (game_state == "YOU LOSE" || game_state == "YOU WIN" || game_state == "INSTRUCTIONS_SCREEN")) {
				GameRestartEvent* gr_event = new GameRestartEvent();
				getGameLogic()->getEventManager()->queueEvent(gr_event);
				game_state = "";
		    }
		    else if ((event.key.code == sf::Keyboard::Space) && (game_state == "START_SCREEN")) {
				game_state = "STORY_SCREEN";
		    }
		    else if ((event.key.code == sf::Keyboard::Space) && (game_state == "STORY_SCREEN")) {
				game_state = "ACTORS_SCREEN";
		    }
		    else if ((event.key.code == sf::Keyboard::Space) && (game_state == "ACTORS_SCREEN")) {
				game_state = "INSTRUCTIONS_SCREEN";
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

void HumanGameView::updateUI()
{
  // Update all the UI elements
  for (UIElement* elem : uiList)
  {
    elem->update(this);
  }
}

// draws the map
void HumanGameView::drawMap() {
	int x_position = map_tl_wcoords.x;
	int y_position = map_tl_wcoords.y;
	
	// these things never change as of right now so they could be created as
	// members of the class...
	int map_size_x = tempMap.get_map_size_x();
	int map_size_y = tempMap.get_map_size_y();
	
	sf::Sprite map_sprite;
	map_sprite.setTexture(texture);
	map_sprite.scale(spriteScale,spriteScale);
	
	for (int y = 0; y < map_size_y; y++) {
        	for (int x = 0; x < map_size_x; x++) {
			map_sprite.setTextureRect(sf::IntRect(25*tempMap.getTerrain(x,y),200,25,25));
			map_sprite.setPosition(sf::Vector2f(x_position,y_position));
			App->draw(map_sprite);
            		x_position += map_tile_size;
        	}
        	x_position = map_tl_wcoords.x;
        	y_position += map_tile_size;
    	}
}

// draws the actors
void HumanGameView::drawActors() {
	sf::Sprite port_sprite;
	port_sprite.setTexture(texture);
	port_sprite.setTextureRect(sf::IntRect(105,0,25,25));

	port_sprite.scale(spriteScale,spriteScale);

	std::map<ActorId, Port*> ports = getGameLogic()->getPortsList();
	for (std::map<ActorId, Port*>::iterator i = ports.begin(); i != ports.end(); i++) {
		if(i->second->isBuyPort()){
			port_sprite.setColor(sf::Color::Red);
		}
		else {
			port_sprite.setColor(sf::Color::Yellow);
		}
		port_sprite.setPosition(sf::Vector2f(i->second->getPositionX() * map_tile_size + map_tl_wcoords.x, i->second->getPositionY() * map_tile_size + map_tl_wcoords.y));
		App->draw(port_sprite);
	}

	sf::Sprite ship_sprite;
	ship_sprite.setTexture(texture);
	
	sf::Sprite kraken_head;
	kraken_head.setTexture(texture);
	kraken_head.setTextureRect(sf::IntRect(96,239,25,25));
	sf::Sprite kraken_tentacle;
	kraken_tentacle.setTexture(texture);
	kraken_tentacle.setTextureRect(sf::IntRect(121,239,25,25));

	ship_sprite.scale(spriteScale,spriteScale);
	const Ship* ship = getGameLogic()->getShip();
	ship_sprite.setPosition(sf::Vector2f(ship->getPositionX() * map_tile_size + map_tl_wcoords.x, ship->getPositionY() * map_tile_size + map_tl_wcoords.y));

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
	
	if (ship->getIsInvincible())
		ship_sprite.setColor(sf::Color::Yellow);

	ship_sprite.setTextureRect(sf::IntRect(0,shipSpriteY,25,25));
	App->draw(ship_sprite);

	lastShipX = ship->getPositionX();
	lastShipY = ship->getPositionY();
	
	const std::map<ActorId, EnemyActor*> *enemies = getGameLogic()->getEnemiesListPointer();
	for (std::map<ActorId, EnemyActor*>::const_iterator i = enemies->begin(); i != enemies->end(); i++) {
		EnemyActor* enemy = i->second;
		if(enemy->getType() == EnemyActor::Pirate || enemy->getType() == EnemyActor::Merchant){
			int enemyShipSpriteY = 0;
			if (enemy->getPrevPos().x > enemy->getPositionX()) {
				enemyShipSpriteY = 25;
			}
			// ship moved right
			else if (enemy->getPrevPos().x < enemy->getPositionX()) {
				enemyShipSpriteY = 50;
			}
			// ship moved up
			else if (enemy->getPrevPos().y > enemy->getPositionY()) {
				enemyShipSpriteY = 75;
			}
			// ship moved down
			else if (enemy->getPrevPos().y < enemy->getPositionY()) {
				enemyShipSpriteY = 0;
			}
			ship_sprite.setTextureRect(sf::IntRect(0,enemyShipSpriteY,25,25));
			
			// changes colors based on various states
			if (enemy->getState() == EnemyActor::Pursue)
				ship_sprite.setColor(sf::Color::Red);
			else if (enemy->getState() == EnemyActor::Stop)
				ship_sprite.setColor(sf::Color::Blue);
			else if (enemy->getRumPenalty() == 0.0)
				ship_sprite.setColor(sf::Color::Cyan);
			else if (enemy->getRumPenalty() > 0.0)
				ship_sprite.setColor(sf::Color(84, 84, 84));
			else
				ship_sprite.setColor(sf::Color::Green);
			
			ship_sprite.setPosition(sf::Vector2f(enemy->getPositionX() * map_tile_size + map_tl_wcoords.x, enemy->getPositionY() * map_tile_size + map_tl_wcoords.y));
			App->draw(ship_sprite);
		}
		if (enemy->getType() == EnemyActor::Kraken) {
			kraken_head.setPosition(sf::Vector2f(enemy->getPositionX() * map_tile_size + map_tl_wcoords.x, enemy->getPositionY() * map_tile_size + map_tl_wcoords.y));
			App->draw(kraken_head);
		}
		if (enemy->getType() == EnemyActor::Tentacle) {
			kraken_tentacle.setPosition(sf::Vector2f(enemy->getPositionX() * map_tile_size + map_tl_wcoords.x, enemy->getPositionY() * map_tile_size + map_tl_wcoords.y));
			if (enemy->getState() == EnemyActor::Pursue)
				kraken_tentacle.setColor(sf::Color::Red);
			App->draw(kraken_tentacle);
		}
	}
}
  
// draws the elements in the UI list
void HumanGameView::drawUI() {
	for ( UIElement* elem : uiList ) {
		elem->draw(App);
	}
}

// draws the screen that the player is on, if any
void HumanGameView::drawScreen() {

	sf::Vector2u window_size = App->getSize();
	double x_scale = window_size.x / 800.0;
	double y_scale = window_size.y / 600.0;

	sf::Sprite screen_sprite;
	if (game_state == "START_SCREEN") {
		screen_sprite.setTexture(start_screen);
	}
	else if (game_state == "YOU LOSE") {
		screen_sprite.setTexture(lose_screen);
	}
	else if (game_state == "YOU WIN") {
		screen_sprite.setTexture(win_screen);
	}
	else if (game_state == "STORY_SCREEN") {
		screen_sprite.setTexture(story_screen);
	}
	else if (game_state == "ACTORS_SCREEN") {
		screen_sprite.setTexture(actors_screen);
	}
	else if (game_state == "INSTRUCTIONS_SCREEN") {
		screen_sprite.setTexture(instructions_screen);
	}
	screen_sprite.setTextureRect(sf::IntRect(0,0,800,600));
	screen_sprite.setPosition(sf::Vector2f(0,0));
	screen_sprite.scale(x_scale,y_scale);
	App->draw(screen_sprite);
}

// handles transaction fails
void HumanGameView::transactionFailEventHandler(const EventInterface& event)
{
  const TransactionFailEvent* tf_event =
    dynamic_cast<const TransactionFailEvent*>(&event);

  if (tf_event == 0)
  {
    return;
  }

  std::ostringstream oss;

  // Why did the transaction fail?  Push descriptive text for each case.
  switch(tf_event->getFailReason())
  {
  case TransactionFailEvent::BUY_EXCEEDS_MAX_SHIP_INVENTORY:
    oss << "Your ship ain't big enough for all this rum!";
    break;

  case TransactionFailEvent::BUY_NOT_ENOUGH_PORT_INVENTORY:
    oss << "We don't have that much rum matey!";
    break;

  case TransactionFailEvent::BUY_NOT_ENOUGH_GOLD:
    oss << "Tryin to cheat me?  You don't have that much gold!";
    break;

  case TransactionFailEvent::SELL_EXCEEDS_SHIP_INVENTORY:
    oss << "There ain't that much rum on your ship!";
    break;

  case TransactionFailEvent::SELL_EXCEEDS_MAX_PORT_INVENTORY:
    oss << "Arr, we can't hold that much rum!";
  };

  oss << "\nSupply: " << tc_portrum << "\nPrice: " << tc_rum_price;
  test->setDialogue(oss.str());
}

// handles transaction successes
void HumanGameView::transactionSuccessEventHandler(const EventInterface& event) {
	std::vector<UIElement*>::iterator position = std::find(uiList.begin(), uiList.end(), test);
	if (position != uiList.end())
		uiList.erase(position);
	menuOpen = false;
}

void HumanGameView::transactionCancelEventHandler(const EventInterface& event) {
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
    tc_rum_price = ts_event->getRumPrice();
	std::ostringstream oss;
	if (ts_event->getIsBuyPort())
		oss << "How much rum ya buyin?\n";
	else
		oss << "How much rum ya sellin?\n";
	oss << "Supply: " << tc_portrum << "\nPrice: " << tc_rum_price;
	test->setDialogue(oss.str());
}

void HumanGameView::gameLostEventHandler(const EventInterface& event) {
	game_state = "YOU LOSE";
}

void HumanGameView::gameWonEventHandler(const EventInterface& event) {
	game_state = "YOU WIN";
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


  // The ratio between the two aspect ratios
  double ar_ratio = map_aspect_ratio / window_aspect_ratio;

  if (ar_ratio > 1.0)
  {
    // The constraining window dimension is the horizontal dimension

    // Update map top-left location
    map_tl_wcoords.x = 0.0;
    map_tl_wcoords.y =
      (currentRes.y - (static_cast<double>(currentRes.y) / ar_ratio)) / 2.0;

    // Update map tile size
    map_tile_size = static_cast<unsigned int>(
      static_cast<double>(window_size.x) /
      static_cast<double>(tempMap.get_map_size_x()));
  }
  else if (ar_ratio < 1.0)
  {
    // The constraining window dimension is the vertical dimension

    // Update the top-left location
    map_tl_wcoords.x =
      (currentRes.x - (static_cast<double>(currentRes.x) * ar_ratio)) / 2.0;
    map_tl_wcoords.y = 0.0;

    // Update the map tile size
    map_tile_size = static_cast<unsigned int>(
      static_cast<double>(window_size.y) /
      static_cast<double>(tempMap.get_map_size_y()));
  }
  else
  {
    // The window dimensions perfectly match the map dimensions.

    // Update the top-left location
    map_tl_wcoords.x = 0;
    map_tl_wcoords.y = 0;

    // Update the map tile size; this is the same as the ar_ratio < 1.0 case
    // above
    map_tile_size = static_cast<unsigned int>(
      static_cast<double>(window_size.y) /
      static_cast<double>(tempMap.get_map_size_y()));
  }
}

bool HumanGameView::mapToWindow(const sf::Vector2f& map_coords,
				sf::Vector2f&       window_coords)
{
  // No conversion possible if input isn't on the map
  if (map_coords.x > tempMap.get_map_size_x() - 1 ||
      map_coords.y > tempMap.get_map_size_y() - 1)
  {
    return false;
  }

  window_coords.x = map_coords.x * map_tile_size + map_tl_wcoords.x;
  window_coords.y = map_coords.y * map_tile_size + map_tl_wcoords.y;

  return true;
}

bool HumanGameView::windowToMap(const sf::Vector2f& window_coords,
				sf::Vector2f&       map_coords)
{
  sf::Vector2u window_size = App->getSize();

  // No conversion possible if input isn't over the map
  if (window_coords.x < map_tl_wcoords.x ||
      window_coords.y < map_tl_wcoords.y ||
      window_coords.x > window_size.x - map_tl_wcoords.x ||
      window_coords.y > window_size.y - map_tl_wcoords.y)
  {
    return false;
  }

  map_coords.x = (window_coords.x - map_tl_wcoords.x) / map_tile_size;
  map_coords.y = (window_coords.y - map_tl_wcoords.y) / map_tile_size;

  return true;
}
