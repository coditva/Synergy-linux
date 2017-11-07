#include <stdio.h>

#include "datatypes.h"
#include "event.h"

void logger(char *message)
{
    printf("Logger: %s\n", message);
}

int print_ev0(message_t *message) { logger("New device"); return 1; }
int print_ev1(message_t *message) { logger("Pair device"); return 1; }
int print_ev2(message_t *message) { logger("Device connected"); return 1; }
int print_ev3(message_t *message) { logger("Device disconnected"); return 1; }
int print_ev4(message_t *message) { logger("New notification"); return 1; }
int print_ev5(message_t *message) { logger("New command"); return 1; }

int plugin_logger_init() {

    event_attach(ET_DEVICE_NEW, print_ev0);
    event_attach(ET_DEVICE_PAIR, print_ev1);
    event_attach(ET_DEVICE_CONNECTED, print_ev2);
    event_attach(ET_DEVICE_DISCONNECTED, print_ev3);
    event_attach(ET_NOTIFICATION, print_ev4);
    event_attach(ET_COMMAND, print_ev5);

    return 1;
}
