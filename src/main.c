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
    plugin_load("get_notif");

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

    fd = args;
    connfd = *fd;

    /* read the stream */
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
                device_pair(connfd);
                break;

            case MT_CONNECT:                /* set a socket for device */
                /* TODO */
                break;

            case MT_NOTIFICATION:
                if (!device_is_paired(buffer.device_id)) {
                    printf("Device is not paired\n");
                    continue;
                }
                event_emit(ET_NOTIFICATION, buffer);
                break;

            default:
                printf("%s\n", "Error!");
        }
    }
    close(connfd);
    return NULL;
}
