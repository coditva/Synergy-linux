#include <stdio.h>
#include <stdlib.h>
#include <libnotify/notify.h>
#include <string.h>

#include "datatypes.h"
#include "event.h"

/*
 * Display the notification using the libnotify library
 */
void send_notif(char *name, char *msg)
{
    notify_init(name);

    NotifyNotification *notif =
        notify_notification_new(name, msg, NULL);
    notify_notification_show(notif, NULL);
}

int display_event_new(payload_t *payload)
{
    send_notif("Synergy", "Found a new device");
    return 1;
}

int display_event_pair(payload_t *payload)
{
    send_notif(payload -> device.name, "Device paired");
    return 1;
}

int display_event_conn(payload_t *payload)
{
    send_notif(payload -> device.name, "Device connected");
    return 1;
}

int display_event_disconn(payload_t *payload)
{
    send_notif("Synergy", "Device disconnected");
    return 1;
}

int plugin_display_events_init() {

    event_attach(ET_DEVICE_CONNECTED, display_event_conn);
    event_attach(ET_DEVICE_DISCONNECTED, display_event_disconn);
    event_attach(ET_DEVICE_NEW, display_event_new);
    event_attach(ET_DEVICE_PAIR, display_event_pair);
    return 1;
}
