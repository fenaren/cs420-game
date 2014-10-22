#if !defined TRANSACTION_CHECK_HANDLER_HPP
#define TRANSACTION_CHECK_HANDLER_HPP

#include <functional>

#include "EventDelegate.hpp"
#include "TransactionCheckEvent.hpp"

/* Define an ActorMovedHandler as a function that takes an ActorMovedEvent and
 * returns nothing. */
typedef std::function<void(const TransactionCheckEvent&)> TransactionCheckHandler;

#endif