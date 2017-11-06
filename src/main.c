#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "server.h"
#include "datatypes.h"
#include "plugin.h"
#include "device.h"
#include "event.h"

int main(int argc, char *argv[])
{
    message_t buffer;
    int connfd;
    device_t *device;

    server_init();
    plugin_load("get_notif");

    while (1) {
        connfd = server_new();
        if (connfd == -1) {
            printf("Fuck!\n");
        } else {
            printf("New connection\n");
        }

        /* read the stream */
        /* TODO: make it async */
        while (read(connfd, &buffer, sizeof(message_t))) {
            if (buffer.special_num != SPECIALNUM)   /* not a message */
                break;

            switch (buffer.type) {

                case MT_HELLO:
                    /* check if device is paired */
                    device = device_get(buffer.message);
                    if (device) {
                        /* device exists as paired */
                        printf("HELLO: Existing\n");
                    } else {
                        /* device is new */
                        printf("HELLO: New\n");
                    }
                    break;

                case MT_PAIR:
                    event_emit(ET_DEVICE_PAIR);
                    device_pair(connfd);
                    break;

                case MT_CONNECT:
                    read(connfd, &buffer, sizeof(message_t));
                    device_connect(buffer.message);

                default:
                    printf("%s\n", "Error!");
            }
        }
        close(connfd);
    }
    return 0;
}
