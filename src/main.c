#include <stdio.h>
#include <unistd.h>

#include "config.h"
#include "server.h"
#include "datatypes.h"
#include "device.h"

int main(int argc, char *argv[])
{
    message_t buffer;
    int connfd;

    server_init();

    while (1) {
        connfd = server_new();

        /* read the stream */
        /* TODO: make it async */
        while (read(connfd, &buffer, sizeof(message_t))) {
            if (buffer.special_num != SPECIALNUM)   /* not a message */
                break;

            switch (buffer.type) {
                case MT_HELLO:
                    device_new(buffer.message);
                    break;
                case MT_PAIR:
                    device_pair(buffer.message);
                    break;
                default:
                    printf("%s\n", "Error!");
            }
        }
        close(connfd);
    }
    return 0;
}
