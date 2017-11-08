#include <unistd.h>
#include <netinet/ip.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "config.h"
#include "datatypes.h"
#include "payload.h"

/* maximum size for message */
#define MAXMESSAGE 100

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in addr;                        /* socket config */
    char buffer[MAXMESSAGE];
    char devid[HASHSIZE];
    payload_t *payload;
    size_t n;
    
    /* create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* put info in addr about the socket */
    bzero(&addr, sizeof(struct sockaddr_in));       /* clear it */
    addr.sin_family = AF_INET;                      /* always to AF_INET */
    addr.sin_port   = htons(PORT);                  /* set port */
    addr.sin_addr.s_addr = inet_addr(HOST);         /* set the host */

    /* connect to the server */
    connect(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));

    /* send hello */
    printf("This is a new device\n");
    printf("Sending HELLO\n");
    payload = payload_create(NULL, MT_HELLO, "\0");
    payload_send(sockfd, payload);
    free(payload);

    /* send pair */
    printf("Sending PAIR\n");
    payload = payload_create(NULL, MT_PAIR, "some device stats");
    payload_send(sockfd, payload);
    free(payload);

    /* read the device id */
    payload = payload_get(sockfd);
    printf("Dev id: %s\n", payload -> message.value);
    strcpy(devid, payload -> message.value);

    while (1) {
        printf(">> ");
        fgets(buffer, MAXMESSAGE, stdin);

        /* send a notification */
        payload = payload_create(devid, MT_NOTIFICATION, buffer);
        payload_send(sockfd, payload);

        free(payload);
    }

    close(sockfd);
}
