#if !defined TRANSACTION_FAIL_HANDLER_HPP
#define TRANSACTION_FAIL_HANDLER_HPP

#include <functional>

#include "EventDelegate.hpp"
#include "TransactionFailEvent.hpp"

/* Define an ActorMovedHandler as a function that takes an ActorMovedEvent and
 * returns nothing. */
typedef std::function<void(const TransactionFailEvent&)> TransactionFailHandler;

#endif