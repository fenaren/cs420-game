#ifndef SHIPMOVECMDEVENT_HPP
#define SHIPMOVECMDEVENT_HPP
#include "EventInterface.hpp"
#include "EventType.hpp"
#include "SFML/Graphics.hpp"
// event that represents the relative move of the ship with a vector
class ShipMoveCmdEvent : public EventInterface {
  public:
  // constructors and destructors
    ShipMoveCmdEvent();
    ShipMoveCmdEvent(sf::Vector2i sMove);
    ~ShipMoveCmdEvent();
    
    static const EventType event_type;
    
    // returns event type
    virtual EventType getEventType() const;
    
    // setters and getters
    void setShipMove(sf::Vector2i sMove);
    sf::Vector2i getShipMove();

private:
    // vector representing a relative ship move
    sf::Vector2i shipMove;
};
#endif


