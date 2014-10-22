#include <SFML/System/Time.hpp>
#include <iostream>
#include "GameLogic.hpp"

void GameLogic::ShipMoveCmdEventHandler(const EventInterface& event)                         
{ 
  unsigned int currentx, currenty, terrain;
  int dirx, diry;
  const ShipMoveCmdEvent* am_event = dynamic_cast<const ShipMoveCmdEvent*>(&event);   
  const EventInterface* shipmovedevent = &shipmoved;
  currentx = ship.getPositionX();
  currenty = ship.getPositionY();
  if (am_event == 0){ 
    std::cout<<"Failed to cast ShipMoveCmdEvent"<<std::endl;
  }else{
    dirx = am_event->getShipMove().x;
    diry = am_event->getShipMove().y;
    //checks map
    terrain = map.getTerrain(currentx+dirx, currenty+diry);
    //does the move
    if (terrain == 0){
      currentx+=dirx;
      currenty+=diry;
      ship.setPositionX(currentx);
      ship.setPositionY(currentx);
    }
    shipmoved.setX(currentx);
    shipmoved.setY(currenty);
    //queues ActorMovedEvent
    event_manager.queueEvent(shipmovedevent);
    //check if ship on port
  }
  
}

void GameLogic::ActorMovedEventHandler(const EventInterface& event)                         
{ 
  unsigned int x, y;
  const ActorMovedEvent* am_event = dynamic_cast<const ActorMovedEvent*>(&event);   

  /* dynamic_cast returns 0 if it couldn't successfully convert the EventInterface
      that was passed in into an ActorMovedEvent */                                         
  if (am_event == 0){ 
    std::cout<<"Failed to cast ActorMovedEvent"<<std::endl;
  }else{
    x = am_event->getX();
    y = am_event->getY();
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



