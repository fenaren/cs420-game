#if !defined EVENT_DELEGATE_HPP
#define EVENT_DELEGATE_HPP

#include <functional>

#include "EventInterface.hpp"

/* Define an EventDelegate as a function that takes an EventInterface and
 * returns nothing. */
typedef std::function<void(const EventInterface&)> EventDelegate;

#endif
