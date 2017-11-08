#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "server.h"
#include "datatypes.h"
#include "plugin.h"
#include "device.h"
#include "event.h"
#include "interface.h"
#include "payload.h"

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
    payload_t *payload;
    device_t *device;
    int *fd, connfd;
    int was_connected = 0;
    char *devname;

    fd = args;
    connfd = *fd;

    devname = (char *) malloc(MAXNAME);

    /* read the stream */
    while (( payload = payload_get(connfd)) != NULL) {

        /* check if message is intented for this app */
        if (payload -> special_num != SPECIALNUM) {
            free(payload);
            break;
        }

        /* attach device name to the payload */
        if (devname != NULL) {
            payload -> device.name = devname;
        }

        switch (payload -> message.type) {

            case MT_HELLO:                  /* check if device is known */
                printf("Got a ping from %s\n", payload -> message.value);
                strcpy(devname, payload -> message.value);
                device = device_get(payload -> device.id);
                if (device) {
                    /* device known */
                    was_connected = 1;
                    event_emit(ET_DEVICE_CONNECTED, payload);
                    free(device);
                } else {
                    /* device is new */
                    event_emit(ET_DEVICE_NEW, payload);
                }
                payload = payload_create(NULL, MT_HELLO, "Linuxer");
                payload_send(connfd, payload);
                free(payload);
                break;

            case MT_PAIR:                   /* pair the device */
                if(interface_ask_yes_no("Do you want to pair?",
                            "Yeah!", "Nah!")) {
                    device = device_pair(devname, payload);
                    event_emit(ET_DEVICE_PAIR, payload);
                    free(payload);

                    payload = payload_create(device -> key, MT_PAIR,
                            device -> id);
                    payload_send(connfd, payload);
                    free(payload);

                    free(device);
                }
                break;

            case MT_NOTIFICATION:           /* device sends a notification */
                device = device_get(devname);
                if (device == NULL) {       /* if device not paired, reject */
                    continue;
                }
                was_connected = 1;
                event_emit(ET_NOTIFICATION, payload);
                free(payload);

                payload = payload_create(device -> key, MT_OK, "OK");
                payload_send(connfd, payload);
                free(payload);

                free(device);
                break;

            default:
                printf("%s\n", "Error!");
                free(payload);
        }
    }

    /* if a device was connected, send a disconnected signal */
    if (was_connected) event_emit(ET_DEVICE_DISCONNECTED, NULL);

    close(connfd);
    return NULL;
}
