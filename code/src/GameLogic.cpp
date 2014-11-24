#include <SFML/System/Time.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "ActorMovedEvent.hpp"
#include "AICmdEvent.hpp"
#include "GameLogic.hpp"
#include "GameLostEvent.hpp"
#include "GameRestartEvent.hpp"
#include "GameWonEvent.hpp"
#include "ShipMoveCmdEvent.hpp"
#include "TransactionCancelEvent.hpp"
#include "TransactionCheckEvent.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionStartEvent.hpp"
#include "TransactionSuccessEvent.hpp"

GameLogic::GameLogic() :
  ship(0)
{
  // Initialize game time
  game_time = 300.0;

  // Initialize game state
  game_over = 0;

  // Initialize the map
  if(!map.createMap("./data/second_map.txt")){
    std::cout<<"Map failed to create"<<std::endl;
  }

  // Initialize all actors
  initializeActors();
}

GameLogic::~GameLogic()
{
  // Iterate over all the actors, deleting them
  for (ActorList::iterator i = actors.begin();
       i != actors.end();
       i++)
  {
    delete i->second;
  }
}

bool GameLogic::initialize()
{
  // Register the proper handler for when the ship move command is triggered
  event_manager.addDelegate(
    EventDelegate(std::bind(&GameLogic::ShipMoveCmdEventHandler,
			    this,
			    std::placeholders::_1)),
    ShipMoveCmdEvent::event_type);
  
  // Register the proper handler for when the transaction check is triggered
  event_manager.addDelegate(
    EventDelegate(std::bind(&GameLogic::TransactionCheckEventHandler,
			    this,
			    std::placeholders::_1)),
    TransactionCheckEvent::event_type);
	
	// Register the proper handler for when the Actor Moved Event is triggered
    event_manager.addDelegate(
    EventDelegate(std::bind(&GameLogic::AICmdEventHandler,
			    this,
			    std::placeholders::_1)),
    AICmdEvent::event_type);

  // Register the proper handler for when the game is restarted
  event_manager.addDelegate(
    EventDelegate(std::bind(&GameLogic::GameRestartEventHandler,
			    this,
			    std::placeholders::_1)),
    GameRestartEvent::event_type);

    // Register the proper handler for collision detection                     
    event_manager.addDelegate(                                                     
    EventDelegate(std::bind(&GameLogic::CollisionEventHandler,                     
                            this,                                                  
                            std::placeholders::_1)),                               
    ActorMovedEvent::event_type);

  return true;
}

void GameLogic::update(const sf::Time& delta_t)
{  
  // Trigger all queued events
  event_manager.processEvents();

  // Update all actors
  for (ActorList::iterator i = actors.begin();
       i != actors.end();
       i++)
  {
    i->second->update(delta_t);
  }

  // Update game_time
  game_time -= delta_t.asSeconds();

  // Check for lose conditions
  if (((ship->getGold() == 0 && ship->getRum() == 0)
	|| game_time <= 0) && game_over == 0) 
  {
    GameLostEvent* gl_event = new GameLostEvent();
    event_manager.queueEvent(gl_event);
    game_over = 1;
  }

  // Check for win condition
  if (ship->getGold() >= 500 && game_over == 0) 
  {
    GameWonEvent* gw_event = new GameWonEvent();
    event_manager.queueEvent(gw_event);
    game_over = 1;
  }  
}

void GameLogic::initializeActors()
{
  // Used for assigning actor IDs throughout this initializer
  unsigned int actor_id = 0;

  // Initialize the ship
  initializeShip(actor_id++);

  // Initialize pirate1
  initializePirate1(actor_id++);

  // Initialize pirate2
  initializePirate2(actor_id++);

  // Create and initialize all the ports
  initializePorts(actor_id++);

  // Create and initialize merchant
  initializeMerchant(actor_id++);

  // Create and initialize kraken
  initializeKraken(actor_id++);
}

void GameLogic::initializeShip(unsigned int actor_id)
{
  // Create and initialize the ship
  ship = new Ship(actor_id);
  ship->setPositionX(10);
  ship->setPositionY(12);
  ship->setMinMoveTime(0.5);
  ship->setGold(10);
  ship->setRum(5);
  ship->setMaxRum(10);
  ship->setRumRate(-0.1);
  ship->initialize();
  ship->setGoldRate(0.0);

  // Push the ship onto the list of actors
  actors[ship->getActorId()] = ship;
}

void GameLogic::initializePirate1(unsigned int actor_id)
{
  // initializer for pirate 1
  pirate1 = new Pirate(actor_id);
  pirate1->initialize();
  pirate1->setPosition(sf::Vector2i(1, 8));
  pirate1->setPrevPos(sf::Vector2i(0, 8));
  enemies[pirate1->getActorId()] = pirate1;
  actors[pirate1->getActorId()] = pirate1;
}

void GameLogic::initializePirate2(unsigned int actor_id)
{
  // initializer for pirate 2
  pirate2 = new Pirate(actor_id);
  pirate2->initialize();
  pirate2->setPosition(sf::Vector2i(26, 10));
  pirate2->setPrevPos(sf::Vector2i(25,10));
  enemies[pirate2->getActorId()] = pirate2;
  actors[pirate2->getActorId()] = pirate2;
}

void GameLogic::initializePorts(unsigned int actor_id)
{
  // Create and initialize all the ports

  // Open the port init file
  std::ifstream ports_init_file("./data/ports.txt");

  // Make sure the file was opened properly
  if (!ports_init_file.fail())
  {
    // Loop over all the lines in the file, initializing ports

    // Delimits tokens in the init file
    char delimiter = ',';
    std::string line;
    while (!ports_init_file.eof())
    {
      // Grab a line and store in 'line'
      std::getline(ports_init_file, line);

      // Push the entire line into a stream so it can be parsed by delimiter
      std::istringstream line_stream(line);

      // All the different parameters that can be read out of the file
      std::string name;
      unsigned int position_x = 0;
      unsigned int position_y = 0;
      double min_move_time    = 0.0;
      double rum              = 0.0;
      double max_rum          = 0.0;
      double rum_rate         = 0.0;

      // Grab everything up to the first delimiter
      std::getline(line_stream, name, delimiter);

      // The name is the first thing on each line, so it could be the name OR it
      // could be the start of comment line.  Search from the start of the name
      // looking for something that's not a space.  If the first character is a #
      // then the line is a comment so we should skip it.  As a side effect trim
      // any leading whitespace off the name field.
      bool pound_found = false;
      for (unsigned int i = 0; i < name.size(); i++)
      {
        if (name[i] != ' ')
        {
          if (name[i] == '#')
          {
            pound_found = true;
          }

          // Go ahead and trim leading whitespace
          name = name.substr(i);
          break;
        }
      }

      if (pound_found)
      {
        continue;
      }

      // Used for consuming delimiters below
      std::string notused;

      // Grab the rest of the data
      line_stream >> position_x;
      std::getline(line_stream, notused, delimiter);
      line_stream >> position_y;
      std::getline(line_stream, notused, delimiter);
      line_stream >> min_move_time;
      std::getline(line_stream, notused, delimiter);
      line_stream >> rum;
      std::getline(line_stream, notused, delimiter);
      line_stream >> max_rum;
      std::getline(line_stream, notused, delimiter);
      line_stream >> rum_rate;

      // Check the failbit, if it's set then the reads above didn't complete
      // correctly, so we don't want to make a port based on it.
      if (line_stream.fail())
      {
        continue;
      }

      // At this point we know we have a good set of port data, so go ahead and
      // start making the Port
      Port* port = new Port(actor_id++);
      port->setPositionX(position_x);
      port->setPositionY(position_y);
      port->setMinMoveTime(min_move_time);
      port->setRum(rum);
      port->setMaxRum(max_rum);
      port->setRumRate(rum_rate);
      port->setName(name);

      // Push this actor onto the actor list
      actors[port->getActorId()] = port;

      // Push this port onto the port list
      ports[port->getActorId()] = port;
    }
  }
  else
  {
    // Just print out some error text if the ports init file wasn't found
    std::cerr << "Port init file not found\n";
  }
}

void GameLogic::initializeMerchant(unsigned int actor_id)
{
  Merchant* merchant = new Merchant(actor_id++);
  merchant->initialize();
  merchant->setPosition(sf::Vector2i(12, 18));
  merchant->setPrevPos(sf::Vector2i(12, 17));
  enemies[merchant->getActorId()] = merchant;
  actors[merchant->getActorId()] = merchant;
}

void GameLogic::initializeKraken(unsigned int actor_id)
{
  KrakenHead* kraken_head = new KrakenHead(actor_id++);
  kraken_head->initialize();
  kraken_head->setPosition(sf::Vector2i(24, 15));
  kraken_head->setPrevPos(sf::Vector2i(23, 15));
  enemies[kraken_head->getActorId()] = kraken_head;
  actors[kraken_head->getActorId()] = kraken_head;
  
  KrakenTentacle* kraken_tent1 = new KrakenTentacle(actor_id++);
  kraken_tent1->initialize();
  kraken_tent1->setPosition(sf::Vector2i(23, 14));
  kraken_tent1->setPrevPos(sf::Vector2i(22, 14));
  kraken_tent1->setLeader(kraken_head);
  kraken_tent1->setFollowOffset(sf::Vector2i(-1, -1));
  enemies[kraken_tent1->getActorId()] = kraken_tent1;
  actors[kraken_tent1->getActorId()] = kraken_tent1;
  
  KrakenTentacle* kraken_tent2 = new KrakenTentacle(actor_id++);
  kraken_tent2->initialize();
  kraken_tent2->setPosition(sf::Vector2i(23, 16));
  kraken_tent2->setPrevPos(sf::Vector2i(22, 16));
  kraken_tent2->setLeader(kraken_head);
  kraken_tent2->setFollowOffset(sf::Vector2i(-1, 1));
  enemies[kraken_tent2->getActorId()] = kraken_tent2;
  actors[kraken_tent2->getActorId()] = kraken_tent2;
  
  KrakenTentacle* kraken_tent3 = new KrakenTentacle(actor_id++);
  kraken_tent3->initialize();
  kraken_tent3->setPosition(sf::Vector2i(25, 14));
  kraken_tent3->setPrevPos(sf::Vector2i(24, 14));
  kraken_tent3->setLeader(kraken_head);
  kraken_tent3->setFollowOffset(sf::Vector2i(1, -1));
  enemies[kraken_tent3->getActorId()] = kraken_tent3;
  actors[kraken_tent3->getActorId()] = kraken_tent3;
  
  KrakenTentacle* kraken_tent4 = new KrakenTentacle(actor_id++);
  kraken_tent4->initialize();
  kraken_tent4->setPosition(sf::Vector2i(25, 16));
  kraken_tent4->setPrevPos(sf::Vector2i(24, 16));
  kraken_tent4->setLeader(kraken_head);
  kraken_tent4->setFollowOffset(sf::Vector2i(1, 1));
  enemies[kraken_tent4->getActorId()] = kraken_tent4;
  actors[kraken_tent4->getActorId()] = kraken_tent4;
}

void GameLogic::resetStartValues()
{
  // Iterate over all the actors, deleting them
  for (ActorList::iterator i = actors.begin();
       i != actors.end();
       i++)
  {
    delete i->second;
  }

  // Reinitialize all actors
  initializeActors();

  // Reset game time
  game_time = 300.0;

  // Reset game state
  game_over = 0;
}

void GameLogic::ShipMoveCmdEventHandler(const EventInterface& event)
{ 
  const ShipMoveCmdEvent* smc_event =
    dynamic_cast<const ShipMoveCmdEvent*>(&event);   
  
  if (smc_event == 0){ 
    std::cout<<"Failed to cast ShipMoveCmdEvent"<<std::endl;
    return;
  }

  // Come up with the position the user wants to move to
  unsigned int new_pos_x = ship->getPositionX() + smc_event->getShipMove().x;
  unsigned int new_pos_y = ship->getPositionY() + smc_event->getShipMove().y;

  // does the move if target terrain is water (this ship can only move on water)
  // AND if enough time has passed
  sf::Vector2i newPos(new_pos_x, new_pos_y);
  if (map.isValidPosition(newPos) &&
      ship->getMoveTime() > ship->getMinMoveTime())
  {
    // Reset the ship's move time, it's just about to move
    ship->setMoveTime(0.0);

    // Set the ship position
    ship->setPositionX(new_pos_x);
    ship->setPositionY(new_pos_y);

    //queues ActorMovedEvent for the ship
    ActorMovedEvent* am_event = new ActorMovedEvent(ship->getActorId(),
						    ship->getPositionX(),
						    ship->getPositionY());
    event_manager.queueEvent(am_event);

    // Now we need to check and see if the ship just moved on top of a port.
    for (PortsList::iterator i = ports.begin();
	 i != ports.end();
	 i++)
    {
      // Is the ship on a port?
      if (ship->getPositionX() == i->second->getPositionX() &&
	  ship->getPositionY() == i->second->getPositionY())
      {
	// Yep, the ship is on a port.  Start a transaction by queueing the
	// TransactionStartEvent
	TransactionStartEvent* ts_event = new TransactionStartEvent();

	ts_event->setShipId(ship->getActorId());
	ts_event->setShipGold(ship->getGold());
	ts_event->setShipRum(ship->getRum());
	ts_event->setPortId(i->second->getActorId());
	ts_event->setPortRum(i->second->getRum());
	ts_event->setRumPrice(i->second->getRumPrice());
	ts_event->setIsBuyPort(i->second->isBuyPort());
	
	event_manager.queueEvent(ts_event);
      }
    }
  }
}  

void GameLogic::AICmdEventHandler(const EventInterface& event) {
	const AICmdEvent* ai_event = dynamic_cast<const AICmdEvent*>(&event);  
	sf::Vector2i newPos = ai_event->getPos();
	EnemyActor* enemy = enemies[ai_event->getActorId()];
	if (enemy->getMoveTime() > enemy->getMinMoveTime() && map.isValidPosition(newPos)) {
		enemy->setMoveTime(0.0);
		enemy->setNeedSeek(false);
		bool otherEnemy = false;
		enemy->setPrevPos(enemy->getPosition());
		enemy->setPosition(newPos);
		ActorMovedEvent* am_event = new ActorMovedEvent(enemy->getActorId(), newPos.x, newPos.y);
		event_manager.queueEvent(am_event);
	}
}

void GameLogic::CollisionEventHandler(const EventInterface& event) {
	const ActorMovedEvent* am_event = dynamic_cast<const ActorMovedEvent*>(&event);  
	bool collision = false;
	EnemyActor *enemy;
	if (am_event->getActorId() == ship->getActorId()) {
		for (EnemiesList::iterator i = enemies.begin(); i != enemies.end() && !collision; i++) {
			if (ship->getPosition() == i->second->getPosition()) {
				enemy = i->second;
				collision = true;
			}
		}
	}
	else {
		EnemiesList::iterator i = enemies.find(am_event->getActorId()); 
		if (i != enemies.end()) {
			enemy = i->second;
			if (enemy->getPosition() == ship->getPosition())
				collision = true;
		}
	}
	if (collision && !ship->getIsInvincible()) {
		int rum_penalty = enemy->getRumPenalty();
		if (enemy->getType() == EnemyActor::Pirate) 
			enemy->setState(EnemyActor::Stop);
		if (rum_penalty > 0) {
			ship->setIsInvincible(true);
			if (rum_penalty <= ship->getRum()) 
				ship->setRum(ship->getRum() - rum_penalty);
			else {
				rum_penalty -= ship->getRum();
				ship->setRum(0);
				int gold_penalty = rum_penalty * 2;
				if (gold_penalty <= ship->getGold()) 
					ship->setGold(ship->getGold() - gold_penalty);
				else 
					ship->setGold(0);
			}
		}
		else if (rum_penalty < 0) {
			if (enemy->getType() == EnemyActor::Merchant)
				enemy->setRumPenalty(0.0);
			ship->setRum(ship->getRum() - rum_penalty);
			if (ship->getRum() > ship->getMaxRum())
				ship->setRum(ship->getMaxRum());
		}
	}
}

void GameLogic::TransactionCheckEventHandler(const EventInterface& event)
{
  unsigned int shipid, portid, price, rum=1;
  unsigned int shipgold, shiprum, shipmaxrum, portrum, rumrequest;

  const TransactionCheckEvent* tcheck_event =
    dynamic_cast<const TransactionCheckEvent*>(&event);

  if (tcheck_event == 0)
  {
    // This should never happen, but just in case
    return;
  }

  // Does the user want to cancel the transaction?
  if (tcheck_event->getCancel())
  {
    // Notify that transaction has been cancelled and return
    TransactionCancelEvent* tc_event = new TransactionCancelEvent();
    event_manager.queueEvent(tc_event);
    
    return;
  }

  shipid = tcheck_event->getShipId();
  portid = tcheck_event->getPortId();
  shipgold = tcheck_event->getShipGold();
  shiprum = tcheck_event->getShipRum();
  shipmaxrum = ship->getMaxRum();
  portrum = tcheck_event->getPortRum();
  rumrequest = tcheck_event->getRumRequest();
  
  price = ports[portid]->getRumPrice();

  // Is this transaction being done with a buy port?
  if (ports[portid]->isBuyPort())
  {
    // Did the ship try to buy too much rum?
    if (rumrequest + shiprum > shipmaxrum)
    {
      TransactionFailEvent* tfail_event =
	new TransactionFailEvent(
	  ship->getActorId(),
	  portid,
	  shipgold,
	  shiprum,
	  portrum,
	  TransactionFailEvent::BUY_EXCEEDS_MAX_SHIP_INVENTORY);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tfail_event);
    }
    // Is the ship trying to buy more rum than the port has?
    else if (rumrequest > portrum)
    {
      TransactionFailEvent* tfail_event =
	new TransactionFailEvent(
	  ship->getActorId(),
	  portid,
	  shipgold,
	  shiprum,
	  portrum,
	  TransactionFailEvent::BUY_NOT_ENOUGH_PORT_INVENTORY);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tfail_event);
    }
    // Is the ship trying to buy more rum than it can afford?
    else if (rumrequest * price > shipgold)
    {
      TransactionFailEvent* tfail_event =
	new TransactionFailEvent(
	  ship->getActorId(),
	  portid,
	  shipgold,
	  shiprum,
	  portrum,
	  TransactionFailEvent::BUY_NOT_ENOUGH_GOLD);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tfail_event);
    }
    else
    {
      // This buy transaction is okay

      ship->setGold(shipgold - (price * rumrequest));
      ship->setRum(shiprum + rumrequest);
      ports[portid]->setRum(portrum - rumrequest);

      // This transaction succeeds so signal that with the
      // TransactionSuccessEvent
      TransactionSuccessEvent* tsuccess_event =
	new TransactionSuccessEvent(ship->getActorId(),
				    portid,
				    shipgold,
				    shiprum,
				    portrum);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tsuccess_event);
    }
  }
  // The transaction is being done with a sell port
  else
  {
    // Is the ship trying to sell more rum than it has?
    if (rumrequest > shiprum)
    {
      TransactionFailEvent* tfail_event =
	new TransactionFailEvent(
	  ship->getActorId(),
	  portid,
	  shipgold,
	  shiprum,
	  portrum,
	  TransactionFailEvent::SELL_EXCEEDS_SHIP_INVENTORY);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tfail_event);
    }
    // Is the ship trying to sell more rum than the port can hold?
    else if (rumrequest + portrum > ports[portid]->getMaxRum())
    {
      TransactionFailEvent* tfail_event =
	new TransactionFailEvent(
	  ship->getActorId(),
	  portid,
	  shipgold,
	  shiprum,
	  portrum,
	  TransactionFailEvent::SELL_EXCEEDS_MAX_PORT_INVENTORY);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tfail_event);
    }
    else
    {
      // This sell transaction is okay

      ship->setGold(shipgold + (price * rumrequest));
      ship->setRum(shiprum - rumrequest);
      ports[portid]->setRum(portrum + rumrequest);

      // This transaction succeeds so signal that with the
      // TransactionSuccessEvent
      TransactionSuccessEvent* tsuccess_event =
	new TransactionSuccessEvent(ship->getActorId(),
				    portid,
				    shipgold,
				    shiprum,
				    portrum);

      // Queue the event, event manager takes ownership
      event_manager.queueEvent(tsuccess_event);
    }
  }
}

void GameLogic::GameRestartEventHandler(const EventInterface& event)
{
  resetStartValues();
}
