#ifndef DATATYPES_H
#define DATATYPES_H

#include "config.h"

/* types of messages that can be passed */
enum message_type {
    MT_HELLO,
    MT_PAIR,
    MT_CONNECT,
    MT_NOTIFICATION,
    MT_OK,
};

typedef struct {
    int special_num;
    struct {
        long unsigned int size;
        enum message_type type;
        char *value;
    } message;
    char device_id[HASHSIZE];
} payload_t;


/* TODO: export events with plugin dev API */
/* types of events that can occur */
typedef enum {
    ET_DEVICE_NEW,
    ET_DEVICE_PAIR,
    ET_DEVICE_CONNECTED,
    ET_DEVICE_DISCONNECTED,
    ET_NOTIFICATION,
    ET_COMMAND,
    ET_SIZE
} event_type_t;

/* event type */
typedef struct {
    event_type_t type;
} event_t;

/* event handler function type */
typedef int (*event_handler_t)(payload_t *);

/* init function handler for plugins */
typedef int (*plugin_init_func_t)(void);
    
/* struct for device identification */
typedef struct {
    char id[HASHSIZE];
    char key[HASHSIZE];
} device_t;

#endif /* end of include guard: DATATYPES_H */
