#include <SFML/System/Time.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

#include "ActorMovedEvent.hpp"
#include "GameLogic.hpp"
#include "ShipMoveCmdEvent.hpp"
#include "TransactionCheckEvent.hpp"
#include "TransactionFailEvent.hpp"
#include "TransactionStartEvent.hpp"
#include "TransactionSuccessEvent.hpp"


GameLogic::GameLogic() :
  ship(0)
{
  // Used for assigning actor IDs throughout this constructor
  unsigned int actor_id = 0;


  // Initialize the map
  if(!map.createMap("./data/second_map.txt")){
    std::cout<<"Map failed to create"<<std::endl;
  }


  // Create and initialize the ship
  ship = new Ship(actor_id++);
  ship->setPositionX(10);
  ship->setPositionY(11);
  ship->setGold(0);
  ship->setRum(1);
  ship->setMaxRum(10);
  ship->setRumRate(0);

  // Push the ship onto the list of actors
  actors[ship->getActorId()] = ship;


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
      double move_time = 0.0;
      double rum       = 0.0;
      double max_rum   = 0.0;
      double rum_rate  = 0.0;

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
      line_stream >> move_time;
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
      port->setMoveTime(move_time);
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
  if (map.getTerrain(new_pos_x, new_pos_y) == Map::WATER)
  {
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
	
	event_manager.queueEvent(ts_event);
      }
    }
  }
}  

void GameLogic::TransactionCheckEventHandler(const EventInterface& event)
{
  unsigned int shipid, portid, price, rum=1;
  double shipgold, shiprum, portrum;

  const TransactionCheckEvent* tcheck_event =
    dynamic_cast<const TransactionCheckEvent*>(&event);

  if (tcheck_event == 0)
  {
    // This should never happen, but just in case
    return;
  }

  shipid = tcheck_event->getShipId();
  portid = tcheck_event->getPortId();
  shipgold = tcheck_event->getShipGold();
  shiprum = tcheck_event->getShipRum();
  portrum = tcheck_event->getPortRum();
  
  price = 11 - portrum;
  
  if (shipgold < price || portrum == 0)
  {
    std::cout<<"Can't buy rum!"<<std::endl;

    // This transaction has failed so signal this with a TransactionFailEvent
    TransactionFailEvent* tfail_event =
      new TransactionFailEvent(ship->getActorId(),
			       portid,
			       shipgold,
			       shiprum,
			       portrum);

    // Queue the event, event manager takes ownership
    event_manager.queueEvent(tfail_event);
  }
  else{
    while (shipgold>price*rum && rum < portrum+1){
      rum ++;
    }
    
    //update ship gold, ship rum, port rum
    shipgold -= price*rum;
    shiprum += rum;
    portrum -= rum;
    
    ship->setRum(shiprum);
    ship->setGold(shipgold);

    // This transaction succeeds so signal that with the TransactionSuccessEvent
    TransactionSuccessEvent* tsuccess_event =
      new TransactionSuccessEvent(ship->getActorId(),
				  portid,
				  shipgold,
				  shiprum,
				  portrum);

    // Queue the event, event manager takes ownership
    event_manager.queueEvent(tsuccess_event);

    // Set the rum of the port that was interacted with
    ports[portid]->setRum(portrum);
  }  
}
