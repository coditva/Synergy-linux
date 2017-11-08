#include <stdio.h>
#include <stdlib.h>
#include <libnotify/notify.h>
#include <string.h>

#include "datatypes.h"
#include "event.h"

/*
 * Display the notification using the libnotify library
 */
int display_notif_send(payload_t *payload)
{
    char name[MAXNAME];
    strcpy(name, payload -> device.name);
    notify_init(name);

    NotifyNotification *notif =
        notify_notification_new(name, payload -> message.value, NULL);
    notify_notification_show(notif, NULL);

    return 1;
}

int plugin_display_notif_init() {

    event_attach(ET_NOTIFICATION, display_notif_send);
    return 1;
}
