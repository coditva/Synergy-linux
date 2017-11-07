#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "config.h"
#include "server.h"
#include "datatypes.h"
#include "plugin.h"
#include "device.h"
#include "event.h"

/* manage the connection as threads */
void * connection_manager(void *args);

/* args */
struct thread_info {
    int t_num;
    pthread_t tid;
    int connfd;
};


int main(int argc, char *argv[])
{
    pthread_attr_t attr;
    int connfd;
    int first, last;
    struct thread_info thread[BACKLOG];

    /* start the server */
    server_init();

    /* load plugins */
    plugin_discover();

    /* init thread attributes */
    pthread_attr_init(&attr);

    first = -1;
    last = 0;
    while (1) {

        /* make it circular */
        if (last == MAXDEVS) {
            last = 0;
            first = 0;
        }

        /* TODO: improve this. some other thread may have finished while
         * waiting for first thread. this will block the threads */
        if (first == last) {
            pthread_join(thread[first].tid, NULL);
            first++;
        }

        /* get a new connection */
        connfd = server_new();
        if (connfd == -1) {
            printf("Connection error\n");
        } else {
            printf("New connection\n");
        }

        /* pass the id as arguments */
        thread[last].connfd = connfd;

        /* create threads */
        pthread_create(&(thread[last].tid), &attr, connection_manager,
                &(thread[last].connfd));

        last++;
    }
    return 0;
}


void * connection_manager(void *args)
{
    message_t buffer;
    device_t *device;
    int *fd, connfd;
    int was_connected = 0;

    fd = args;
    connfd = *fd;

    /* read the stream */
    while (read(connfd, &buffer, sizeof(message_t))) {

        /* check if message is intented for this app */
        if (buffer.special_num != SPECIALNUM) {
            break;
        }

        switch (buffer.type) {

            case MT_HELLO:                  /* check if device is known */
                device = device_get(buffer.device_id);
                if (device) {
                    /* device known */
                    was_connected = 1;
                    event_emit(ET_DEVICE_CONNECTED, buffer);
                } else {
                    /* device is new */
                    event_emit(ET_DEVICE_NEW, buffer);
                }
                break;

            case MT_PAIR:                   /* pair the device */
                event_emit(ET_DEVICE_PAIR, buffer);
                device_pair(connfd);
                break;

            case MT_NOTIFICATION:           /* device sends a notification */
                /* check if device is paired */
                if (!device_is_paired(buffer.device_id)) {
                    continue;
                }
                was_connected = 1;
                event_emit(ET_NOTIFICATION, buffer);
                break;

            default:
                printf("%s\n", "Error!");
        }
    }

    /* if a device was connected, send a disconnected signal */
    if (was_connected) event_emit(ET_DEVICE_DISCONNECTED, buffer);

    close(connfd);
    return NULL;
}
