#ifndef DATATYPES_H
#define DATATYPES_H

#define MAXMESSAGE 100

enum message_type {
    MT_HELLO,
    MT_NEW,
    MT_PAIR,
};

typedef enum event_type {
    ET_DEVICE_NEW,
    ET_DEVICE_PAIR,
    ET_NOTIFICATION,
    ET_COMMAND,
    ET_SIZE
} event_type_t;

/* TODO: optimize this data struct */
typedef struct message_struct {
    int special_num;
    enum message_type type;
    char message[MAXMESSAGE];
} message_t;

typedef int (*plugin_init_func_t)(void);

typedef struct event_struct {
    enum event_type type;
} event_t;

typedef void (*event_handler_t)(void);
    

#endif /* end of include guard: DATATYPES_H */
