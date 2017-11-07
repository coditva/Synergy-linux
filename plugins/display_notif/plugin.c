#include <stdio.h>
#include <stdlib.h>
#include <libnotify/notify.h>

#include "datatypes.h"
#include "event.h"

/*
 * Display the notification using the libnotify library
 */
int display_notif_send(message_t *message)
{
    char name[] = "Synergy";
    notify_init(name);

    NotifyNotification *notif = notify_notification_new(name, message -> message, NULL);
    notify_notification_show(notif, NULL);

    return 1;
}

int plugin_display_notif_init() {

    event_attach(ET_NOTIFICATION, display_notif_send);
    return 1;
}
