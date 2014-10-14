#if !defined EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <list>
#include <map>

#include "EventDelegate.hpp"
#include "EventInterface.hpp"
#include "EventType.hpp"

class EventManager
{
public:

  EventManager();

  ~EventManager();

  void queueEvent(const EventInterface* event);

  void triggerEvent(const EventInterface& event);

  void processEvents();

  void addDelegate(const EventDelegate& event_delegate, EventType event_type);

private:

  // EventQueues are a list of events
  typedef std::list<const EventInterface*> EventQueue;

  // EventDelegates are lists of EventDelegate
  typedef std::list<EventDelegate> EventDelegates;

  // The EventMap maps event types to a list of delegates associated with that
  // event
  typedef std::map<EventType, EventDelegates> EventMap;

  // EventManager maintains two queues.  Events are registered into one and
  // processed out of the other.  The two queues switch between register and
  // process duty every time events are processed.
  EventQueue event_queue[2];

  // New events are registered into the register queue, and events are processed
  // out of the process queue.
  EventQueue* process_queue;
  EventQueue* register_queue;

  // This is how EventManager knows what delegates to call when a specific event
  // is triggered
  EventMap event_map;
};

#endif
