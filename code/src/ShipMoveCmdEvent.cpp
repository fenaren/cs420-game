#include "ShipMoveCmdEvent.hpp"

const EventType ShipMoveCmdEvent::event_type = EventType(&ShipMoveCmdEvent::event_type);

ShipMoveCmdEvent::ShipMoveCmdEvent()
{
}

ShipMoveCmdEvent::ShipMoveCmdEvent(sf::Vector2i sMove) {
  shipMove = sMove;
}

ShipMoveCmdEvent::~ShipMoveCmdEvent() {
}

EventType ShipMoveCmdEvent::ShipMoveCmdEvent::getEventType() const
{
  return event_type;
}

// set the ship move vector
void ShipMoveCmdEvent::setShipMove(sf::Vector2i sMove) {
  shipMove = sMove;
}

// returns the vector representing the requested ship move
// note: (1, 0) move right, (-1, 0) move left
// (0, 1) move up, (0, -1) move down
// (1, 1) move up-right, (-1, 1) move up-left
// (1, -1) move down-right, (-1, -1) move down-left
sf::Vector2i ShipMoveCmdEvent::getShipMove() const{
  return shipMove;
}