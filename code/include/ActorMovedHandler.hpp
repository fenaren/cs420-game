#if !defined ACTOR_MOVED_HANDLER_HPP
#define ACTOR_MOVED_HANDLER_HPP

#include <functional>

#include "EventDelegate.hpp"
#include "ActorMovedEvent.hpp"

/* Define an ActorMovedHandler as a function that takes an ActorMovedEvent and
 * returns nothing. */
typedef std::function<void(const ActorMovedEvent&)> ActorMovedHandler;

#endif