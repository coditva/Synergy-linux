#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"
#include "event.h"

/* a linked list to store the event handlers */
struct event_item {
    event_handler_t handler;
    struct event_item *next;
};
struct event_item_list {
    struct event_item *top;
    struct event_item *last;
} event_list[ET_SIZE];


/*
 * Runs all the events attached to a particular event type
 * @param event_type_t the type of event to emit
 * @param message_t the message received by the device
 */
void event_emit(event_type_t event_type, message_t message)
{
    struct event_item *item = event_list[event_type].top;

    printf("Event: %d\n", event_type);

    /* TODO: make it async */
    while (item != NULL) {
        (*(item -> handler))(&message);         /* run the handler */
        item = item -> next;                    /* increment */
    }
}

/*
 * Puts the given event handler in the list of events associated with the
 * given event type
 * @param event_type_t the type of event
 * @param event_handler the handler to be added
 */
void event_attach(event_type_t event_type, event_handler_t event_handler)
{
    /* create a new event list item */
    struct event_item *new_event_item =
        (struct event_item *) malloc(sizeof(struct event_item));
    new_event_item -> next = NULL;
    new_event_item -> handler = event_handler;

    /* if list is empty, add to the top else add at the end */
    if (event_list[event_type].top == NULL) {
        event_list[event_type].top = new_event_item;
        event_list[event_type].last = new_event_item;
    } else {
        event_list[event_type].last -> next = new_event_item;
        event_list[event_type].last = new_event_item;
    }
}
