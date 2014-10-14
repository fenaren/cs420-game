#include <list>
#include <map>

#include "EventDelegate.hpp"
#include "EventInterface.hpp"
#include "EventManager.hpp"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::queueEvent(const EventInterface* event)
{
  register_queue->push_back(event);
}

void EventManager::triggerEvent(const EventInterface& event)
{
  // Get the event delegates associated with this event
  EventMap::iterator i = event_map.find(event.getEventType());

  // If this event hasn't ever been registered just leave
  if (i == event_map.end())
  {
    return;
  }

  // Now loop over all the delegates, calling them.
  //EventDelegates::iterator delegate = i->second;
}

void EventManager::addDelegate(const EventDelegate& event_delegate,
			       EventType            event_type)
{
  // Just push the delegate onto the list associated with event_type.  The class
  // slides search the list to make sure the delegate isn't already registered,
  // but doing that isn't as easy as shown in the slides
  event_map[event_type].push_back(event_delegate);
}
