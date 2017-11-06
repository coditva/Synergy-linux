#ifndef EVENT_H
#define EVENT_H

/* emit an event */
void event_emit(event_type_t event, message_t message);

/* attach an event handler to an event */
void event_attach(event_type_t event_type, event_handler_t event_handler);

#endif /* end of include guard: EVENT_H */
