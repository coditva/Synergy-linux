#include <unistd.h>
#include <netinet/ip.h>
#include <strings.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "config.h"
#include "datatypes.h"
#include "server.h"
#include "device.h"

#define BACKLOG 10

int server_main;

void server_init()
{
    int sockfd;
    struct sockaddr_in addr;                        /* socket config */
    
    /* create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* put info in addr about the socket */
    bzero(&addr, sizeof(struct sockaddr_in));       /* clear it */
    addr.sin_family = AF_INET;                      /* always to AF_INET */
    addr.sin_port   = htons(PORT);                  /* set port */
    addr.sin_addr.s_addr = inet_addr(HOST);         /* set the host */

    /* bind the socket to an address */
    bind(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));

    /* mark socket as passive, which will accept connections later */
    listen(sockfd, BACKLOG);
    server_main = sockfd;
}

void server_accept()
{
    int connfd;
    message_t buffer;

    while (1) {
        /* create a socket for each connection request */
        connfd = accept(server_main, NULL, NULL);

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
}
