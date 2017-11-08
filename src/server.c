#include <unistd.h>
#include <netinet/ip.h>
#include <strings.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "config.h"
#include "datatypes.h"
#include "server.h"

/* store the server file descriptor */
int server_main;

/*
 * Make the server listen passively on the host and port given in the config.h
 */
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

/*
 * Return the top connection to the server from the waiting list
 * @return int file descriptor for the socket
 */
int server_new()
{
    return accept(server_main, NULL, NULL);
}
