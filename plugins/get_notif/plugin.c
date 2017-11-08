#include <stdio.h>

#include "datatypes.h"
#include "event.h"

int echo_notif(payload_t *payload)
{
    printf("Notif: %s\n", payload -> message.value);
    return 1;
}

int plugin_get_notif_init() {
    event_attach(ET_NOTIFICATION, echo_notif);
    return 1;
}
