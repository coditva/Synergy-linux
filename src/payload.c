#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "datatypes.h"
#include "config.h"
#include "payload.h"

payload_t * payload_get(int fd)
{
    payload_t *buffer;

    buffer = (payload_t *) malloc(sizeof(payload_t));
    read(fd, buffer, sizeof(payload_t));

    buffer -> message.value = (char *) malloc(buffer -> message.size);
    read(fd, buffer -> message.value, buffer -> message.size);

    return buffer;
}

void payload_send(int fd, payload_t *payload)
{
    write(fd, payload, sizeof(payload_t));
    write(fd, payload -> message.value, payload -> message.size);
}

payload_t * payload_create(char *device_id, enum message_type type, char *message)
{
    payload_t *buffer;

    buffer = (payload_t *) malloc(sizeof(payload_t));

    buffer -> special_num = SPECIALNUM;
    buffer -> message.type = type;
    buffer -> message.size = strlen(message) + 1;
    buffer -> message.value = (char *) malloc(buffer -> message.size);
    strcpy(buffer -> message.value, message);
    if (device_id != NULL) strcpy(buffer -> device_id, device_id);

    return buffer;
}
