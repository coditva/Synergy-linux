#include <stdio.h>

#include "datatypes.h"
#include "event.h"

int echo_notif(message_t *message)
{
    printf("Notif: %s\n", message -> message);
    return 1;
}

int plugin_get_notif_init() {
    printf("inside Get_notif_init\n");

    event_attach(ET_NOTIFICATION, echo_notif);
    return 1;
}
