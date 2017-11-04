#include <unistd.h>
#include <netinet/ip.h>
#include <strings.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "config.h"
#include "datatypes.h"
#include "server.h"

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

int server_new()
{
    /* TODO: store peer details too */
    return accept(server_main, NULL, NULL);
}
