#if !defined TRANSACTION_SUCCESS_HANDLER_HPP
#define TRANSACTION_SUCCESS_HANDLER_HPP

#include <functional>

#include "EventDelegate.hpp"
#include "TransactionSuccessEvent.hpp"

/* Define an ActorMovedHandler as a function that takes an ActorMovedEvent and
 * returns nothing. */
typedef std::function<void(const TransactionSuccessEvent&)> TransactionSuccessEvent;

#endif