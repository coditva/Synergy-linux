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
                    event_emit(ET_DEVICE_NEW);
                    read(connfd, &buffer, sizeof(message_t));
                    device_new(buffer.message);
                    break;

                case MT_PAIR:
                    event_emit(ET_DEVICE_PAIR);
                    read(connfd, &buffer, sizeof(message_t));
                    device_pair(buffer.message);
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
