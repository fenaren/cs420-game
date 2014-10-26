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

  /* Queue up an event to be triggered the next time processEvents() is
   * called.  EventManager DOES take ownership of the event when this is
   * called (EventManager DOES delete the event). */
  void queueEvent(const EventInterface* event);

  /* Instantly trigger the given event */
  void triggerEvent(const EventInterface& event);

  /* Trigger all the events that have been queued with queueEvent().  Calling
     this empties the queue. */
  void processEvents();

  /* Associate a delegate function with a given event type.  EventManager
   * copies the specified EventDelegate into its internals when this function
   * is called.  Best way to use is like this:

   event_manager.addDelegate(EventDelegate(your_event_handler),
                                           YourEvent::event_type);
  */
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
