#ifndef DATATYPES_H
#define DATATYPES_H

#include "config.h"

/* types of messages that can be passed */
enum message_type {
    MT_HELLO,
    MT_PAIR,
    MT_CONNECT,
    MT_NOTIFICATION,
};

/* TODO: optimize this data struct */
typedef struct message_struct {
    int special_num;
    char device_id[HASHSIZE];
    enum message_type type;
    char message[MAXMESSAGE];
} message_t;


/* TODO: export events with plugin dev API */
/* types of events that can occur */
typedef enum event_type {
    ET_DEVICE_NEW,
    ET_DEVICE_PAIR,
    ET_DEVICE_CONNECTED,
    ET_DEVICE_DISCONNECTED,
    ET_NOTIFICATION,
    ET_COMMAND,
    ET_SIZE
} event_type_t;

/* event type */
typedef struct event_struct {
    enum event_type type;
} event_t;

/* event handler function type */
typedef int (*event_handler_t)(message_t *);

/* init function handler for plugins */
typedef int (*plugin_init_func_t)(void);
    
/* struct for device identification */
typedef struct device_struct {
    char *id;
} device_t;

#endif /* end of include guard: DATATYPES_H */
