#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"
#include "event.h"

struct event_item {
    event_handler_t handler;
    struct event_item *next;
};

struct event_item_list {
    struct event_item *top;
    struct event_item *last;
} event_list[ET_SIZE];


void event_emit(event_type_t event_type, message_t message)
{
    struct event_item *item = event_list[event_type].top;

    printf("Event: %d\n", event_type);

    /* TODO: make it async */
    while (item != NULL) {
        (*(item -> handler))(&message);
        item = item -> next;
    }
}

void event_attach(event_type_t event_type, event_handler_t event_handler)
{
    struct event_item *new_event_item =
        (struct event_item *) malloc(sizeof(struct event_item));
    new_event_item -> next = NULL;
    new_event_item -> handler = event_handler;

    if (event_list[event_type].top == NULL) {
        event_list[event_type].top = new_event_item;
        event_list[event_type].last = new_event_item;
    } else {
        event_list[event_type].last -> next = new_event_item;
        event_list[event_type].last = new_event_item;
    }
}
