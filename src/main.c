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
            if (buffer.special_num != SPECIALNUM)
                break;                          /* not a message */

            switch (buffer.type) {

                case MT_HELLO:                  /* check if device is known */
                    device = device_get(buffer.device_id);
                    if (device) printf("HELLO: Exists\n"); /* device known */
                    else printf("HELLO: New\n"); /* device is new */
                    break;

                case MT_PAIR:                   /* pair the device */
                    printf("Pairing\n");
                    event_emit(ET_DEVICE_PAIR);
                    device_pair(connfd);
                    break;

                case MT_CONNECT:                /* set a socket for device */
                    device_connect(buffer.message);
                    break;

                case MT_NOTIFICATION:
                    printf("Notif: %s\n", buffer.message);
                    break;

                default:
                    printf("%s\n", "Error!");
            }
        }
        close(connfd);
    }
    return 0;
}
