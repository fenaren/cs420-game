#include <SFML/System/Time.hpp>
#include <iostream>

#include "GameLogic.hpp"

void GameLogic::ShipMoveCmdEventHandler(const EventInterface& event)
{ 
  unsigned int currentx, currenty, port1x, port1y, port2x, port2y, port3x, port3y, port4x, port4y, terrain;
  int dirx, diry;

  const ShipMoveCmdEvent* smc_event =
    dynamic_cast<const ShipMoveCmdEvent*>(&event);   
  
  currentx = ship.getPositionX();
  currenty = ship.getPositionY();
  port1x = port1.getPositionX();
  port1y = port1.getPositionY();
  port2x = port2.getPositionX();
  port2y = port2.getPositionY();
  port3x = port3.getPositionX();
  port3y = port3.getPositionY();
  port4x = port4.getPositionX();
  port4y = port4.getPositionY();
  
  if (smc_event == 0){ 
    std::cout<<"Failed to cast ShipMoveCmdEvent"<<std::endl;
  }else{
    dirx = smc_event->getShipMove().x;
    diry = smc_event->getShipMove().y;
    
    //checks map
    terrain = map.getTerrain(currentx+dirx, currenty+diry);
    
    //does the move if terrain is water
    if (terrain == 0){
      currentx+=dirx;
      currenty+=diry;
      ship.setPositionX(currentx);
      ship.setPositionY(currenty);
    }

    //queues ActorMovedEvent for the ship
    ActorMovedEvent* am_event = new ActorMovedEvent(ship.getActorId(),
						    ship.getPositionX(),
						    ship.getPositionY());
    event_manager.queueEvent(am_event);


    // If the ship is on a port a transaction is starting.  Signal that this
    // is happening with the TransactionStartEvent.

    TransactionStartEvent* ts_event = new TransactionStartEvent();
    ts_event->setShipId(ship.getActorId());
    ts_event->setShipGold(ship.getGold());
    ts_event->setShipRum(ship.getRum());
    
    //check if ship on port
    if(currentx==port1x && currenty ==port1y)
    {
      // Set up the event with the appropriate data
      ts_event->setPortId(port1.getActorId());
      ts_event->setPortRum(port1.getRum());
    }
    else if(currentx==port2x && currenty ==port2y)
    {
      // Set up the event with the appropriate data
      ts_event->setPortId(port2.getActorId());
      ts_event->setPortRum(port2.getRum());
    }
    else if(currentx==port3x && currenty ==port3y)
    {
      // Set up the event with the appropriate data
      ts_event->setPortId(port3.getActorId());
      ts_event->setPortRum(port3.getRum());
    }
    else if(currentx==port4x && currenty ==port4y)
    {
      // Set up the event with the appropriate data
      ts_event->setPortId(port4.getActorId());
      ts_event->setPortRum(port4.getRum());
    }

    // Queue the transaction start, event manager takes ownership
    event_manager.queueEvent(ts_event);
  }  
}

void GameLogic::TransactionStartEventHandler(const EventInterface& event)
{
  const TransactionStartEvent* tstart_event =
    dynamic_cast<const TransactionStartEvent*>(&event);
}

void GameLogic::TransactionCheckEventHandler(const EventInterface& event)
{
  unsigned int shipid, portid, price, rum=1;
  double shipgold, shiprum, portrum;

  const TransactionCheckEvent* tcheck_event =
    dynamic_cast<const TransactionCheckEvent*>(&event);

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
      new TransactionFailEvent(ship.getActorId(),
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
    
    ship.setRum(shiprum);
    ship.setGold(shipgold);

    // This transaction succeeds so signal that with the TransactionSuccessEvent
    TransactionSuccessEvent* tsuccess_event =
      new TransactionSuccessEvent(ship.getActorId(),
				  portid,
				  shipgold,
				  shiprum,
				  portrum);

    // Queue the event, event manager takes ownership
    event_manager.queueEvent(tsuccess_event);

    if(portid==1){
      port1.setRum(portrum);
    }else if(portid ==2){
      port2.setRum(portrum);
    }else if(portid ==3){
      port3.setRum(portrum);
    }else if(portid ==4){
      port4.setRum(portrum);
    }
  }
  
}

void GameLogic::TransactionFailEventHandler(const EventInterface& event)
{
  const TransactionFailEvent* tfail_event =
    dynamic_cast<const TransactionFailEvent*>(&event);
}


void GameLogic::TransactionSuccessEventHandler(const EventInterface& event)
{
  const TransactionSuccessEvent* tsuccess_event =
    dynamic_cast<const TransactionSuccessEvent*>(&event);
}


GameLogic::GameLogic():
  ship(0),
  port1(1),
  port2(2),
  port3(3),
  port4(4),
  map()
{
  if(!map.createMap("./second_map.txt")){
    std::cout<<"Map failed to create"<<std::endl;
  }

  ActorList actor_list;
  actor_list.push_back(&ship);
  actor_list.push_back(&port1);
  actor_list.push_back(&port2);
  actor_list.push_back(&port3);
  actor_list.push_back(&port4);
}

GameLogic::~GameLogic()
{
}

bool GameLogic::initialize()
{
  /*event_manager.addDelegate(ActorMovedEventHandler, ActorMovedEvent().getEventType());
  event_manager.addDelegate(ShipMoveCmdEventHandler, ShipMoveCmdEvent().getEventType());*/
  return true;
}

void GameLogic::update(const sf::Time& delta_t)
{
  // Trigger all queued events
  event_manager.processEvents();
  
}



