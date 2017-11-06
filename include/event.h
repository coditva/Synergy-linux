#ifndef EVENT_H
#define EVENT_H

void event_emit(event_type_t event, message_t message);
void event_attach(event_type_t event_type, event_handler_t event_handler);

#endif /* end of include guard: EVENT_H */
