#include <SFML/System/Time.hpp>
#include <iostream>
#include "GameLogic.hpp"

void GameLogic::ShipMoveCmdEventHandler(const EventInterface& event)                         
{ 
  unsigned int currentx, currenty, port1x, port1y, port2x, port2y, port3x, port3y, port4x, port4y, terrain;
  int dirx, diry;
  const ShipMoveCmdEvent* am_event = dynamic_cast<const ShipMoveCmdEvent*>(&event);   
  const EventInterface* shipmovedevent = &shipmoved;
  
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
  
  if (am_event == 0){ 
    std::cout<<"Failed to cast ShipMoveCmdEvent"<<std::endl;
  }else{
    dirx = am_event->getShipMove().x;
    diry = am_event->getShipMove().y;
    
    //checks map
    terrain = map.getTerrain(currentx+dirx, currenty+diry);
    
    //does the move if terrain is water
    if (terrain == 0){
      currentx+=dirx;
      currenty+=diry;
      ship.setPositionX(currentx);
      ship.setPositionY(currenty);
    }
    shipmoved.setX(currentx);
    shipmoved.setY(currenty);
    
    //queues ActorMovedEvent
    event_manager.queueEvent(shipmovedevent);
    
    //check if ship on port
    if(currentx==port1x && currenty ==port1y){
      const EventInterface* sport1 = &startport1;
      startport1.setShipGold(ship.getGold());
      startport1.setShipRum(ship.getRum());
      startport1.setPortRum(port1.getRum());
      event_manager.queueEvent(sport1);
    }else if(currentx==port2x && currenty ==port2y){
      const EventInterface* sport2 = &startport2;
      startport2.setShipGold(ship.getGold());
      startport2.setShipRum(ship.getRum());
      startport2.setPortRum(port2.getRum());
      event_manager.queueEvent(sport2);
    }else if(currentx==port3x && currenty ==port3y){
      const EventInterface* sport3 = &startport3;
      startport3.setShipGold(ship.getGold());
      startport3.setShipRum(ship.getRum());
      startport3.setPortRum(port3.getRum());
      event_manager.queueEvent(sport3);
    }else if(currentx==port4x && currenty ==port4y){
      const EventInterface* sport4 = &startport4;
      startport4.setShipGold(ship.getGold());
      startport4.setShipRum(ship.getRum());
      startport4.setPortRum(port4.getRum());
      event_manager.queueEvent(sport4);
    }
  }
  
}

void GameLogic::ActorMovedEventHandler(const EventInterface& event)                         
{ 
  unsigned int x, y, actorId;
  const ActorMovedEvent* am_event = dynamic_cast<const ActorMovedEvent*>(&event);   

  /* dynamic_cast returns 0 if it couldn't successfully convert the EventInterface
      that was passed in into an ActorMovedEvent */                                         
  if (am_event == 0){ 
    std::cout<<"Failed to cast ActorMovedEvent"<<std::endl;
  }else{
    x = am_event->getX();
    y = am_event->getY();
    
    actorId = am_event->getActorId();
    
    if (actorId == 0){
      ship.setPositionX(x);
      ship.setPositionY(y);
    }else if(actorId == 1){
      port1.setPositionX(x);
      port1.setPositionY(y);
    }else if(actorId == 2){
      port2.setPositionX(x);
      port2.setPositionY(y);
    }else if(actorId == 3){
      port3.setPositionX(x);
      port3.setPositionY(y);
    }else if(actorId == 4){
      port4.setPositionX(x);
      port4.setPositionY(y);
    }else{
      std::cout<<"actorId not found"<<std::endl; 
    }
  }
}

GameLogic::GameLogic():
  ship(0),
  port1(1),
  port2(2),
  port3(3),
  port4(4),
  map(),
  shipmoved(),
  port1moved(),
  port2moved(),
  port3moved(),
  port4moved()
{
  if(!map.createMap("map.txt")){
    std::cout<<"Map failed to create"<<std::endl;
  }
  ActorList actor_list;
  actor_list.push_back(&ship);
  actor_list.push_back(&port1);
  actor_list.push_back(&port2);
  actor_list.push_back(&port3);
  actor_list.push_back(&port4);
  
  shipmoved.setActorId(0);
  port1moved.setActorId(1);
  port2moved.setActorId(2);
  port3moved.setActorId(3);
  port4moved.setActorId(4);
  
  startport1.setShipId(0);
  startport1.setPortId(1);
  startport2.setShipId(0);
  startport2.setPortId(2);
  startport3.setShipId(0);
  startport3.setPortId(3);
  startport4.setShipId(0);
  startport4.setPortId(4);
  
  checkport1.setShipId(0);
  checkport1.setPortId(1);
  checkport2.setShipId(0);
  checkport2.setPortId(2);
  checkport3.setShipId(0);
  checkport3.setPortId(3);
  checkport4.setShipId(0);
  checkport4.setPortId(4);
  
  successport1.setShipId(0);
  successport1.setPortId(1);
  successport2.setShipId(0);
  successport2.setPortId(2);
  successport3.setShipId(0);
  successport3.setPortId(3);
  successport4.setShipId(0);
  successport4.setPortId(4);
  
  failport1.setShipId(0);
  failport1.setPortId(1);
  failport2.setShipId(0);
  failport2.setPortId(2);
  failport3.setShipId(0);
  failport3.setPortId(3);
  failport4.setShipId(0);
  failport4.setPortId(4);
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



