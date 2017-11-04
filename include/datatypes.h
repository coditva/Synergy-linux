#ifndef DATATYPES_H
#define DATATYPES_H

#define MAXMESSAGE 100

enum message_type {
    MT_HELLO,
    MT_NEW,
    MT_PAIR,
};

/* TODO: optimize this data struct */
typedef struct message_struct {
    int special_num;
    enum message_type type;
    char message[MAXMESSAGE];
} message_t;

typedef int (*init_func_t)(void);

#endif /* end of include guard: DATATYPES_H */
