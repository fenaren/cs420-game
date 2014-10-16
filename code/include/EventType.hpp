#if !defined EVENT_TYPE_HPP
#define EVENT_TYPE_HPP

/* Define EventType as a unsigned long long int.  unsigned long long int is
 * guaranteed by the C standard to be at least 8 bytes.  8 bytes are needed
 * because it is recommended that EventTypes be set using the memory location of
 * the event class they are associated with, and these can be at most 8 bytes. */
typedef unsigned long long int EventType;

#endif
