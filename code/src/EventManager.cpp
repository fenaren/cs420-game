#include <algorithm>
#include <list>
#include <map>

#include "EventDelegate.hpp"
#include "EventInterface.hpp"
#include "EventManager.hpp"

EventManager::EventManager() :
  process_queue(&event_queue[0]),
  register_queue(&event_queue[1])
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

  // Grab all the delegates associated with this event
  EventDelegates* event_delegates = &i->second;

  // Loop over them all, calling them
  for (EventDelegates::iterator ed_iter = event_delegates->begin();
       ed_iter != event_delegates->end();
       ed_iter++)
  {
    (*ed_iter)(event);
  }
}

void EventManager::processEvents()
{
  // Turn the register queue into the process queue
  std::swap(register_queue, process_queue);

  // Process all the events out of the process queue
  while(!process_queue->empty())
  {
    const EventInterface* event = process_queue->front();
    process_queue->pop_front();

    triggerEvent(*event);
  }
}

void EventManager::addDelegate(const EventDelegate& event_delegate,
			       EventType            event_type)
{
  // Just push the delegate onto the list associated with event_type.  The class
  // slides search the list to make sure the delegate isn't already registered,
  // but doing that isn't as easy as shown in the slides
  event_map[event_type].push_back(event_delegate);
}
