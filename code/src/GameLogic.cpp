#include <SFML/System/Time.hpp>
#include <iostream>
#include "GameLogic.hpp"

void ShipMoveCmdEventHandler(const EventInterface& event)                         
{ 
  unsigned int currentx, currenty, dirx, diry;
  EventManager event_manager;
  const ShipMoveCmdEvent* am_event = dynamic_cast<const ShipMoveCmdEvent*>(&event);   
                             
  if (am_event == 0){ 
    std::cout<<"Failed to cast ShipMoveCmdEvent"<<std::endl;
  }else{
      
  }
  
}

void ActorMovedEventHandler(const EventInterface& event)                         
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
  port4(4)
{
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
  return true;
}

void GameLogic::update(const sf::Time& delta_t)
{
  // Trigger all queued events
  event_manager.processEvents();
  event_manager.addDelegate(ActorMovedEventHandler, ActorMovedEvent().getEventType());
  event_manager.addDelegate(ShipMoveCmdEventHandler, ShipMoveCmdEvent().getEventType());
}



