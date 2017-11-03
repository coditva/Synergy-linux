#include <unistd.h>
#include <netinet/ip.h>
#include <strings.h>
#include <stdio.h>
#include <arpa/inet.h>

#include "server.h"

#define PORT 3020
#define HOST "127.0.0.1"
#define BACKLOG 10
#define BUFFERSIZE 100

void server_create()
{
    int sockfd, connfd;
    struct sockaddr_in addr;                        /* socket config */
    struct sockaddr peer_addr;                      /* peer details */
    socklen_t peer_addr_size;
    char buffer[BUFFERSIZE];
    
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

    /* create a socket for each connection request */
    connfd = accept(sockfd, &peer_addr, &peer_addr_size);

    while (read(connfd, buffer, BUFFERSIZE)) {
        printf("%s\n", buffer);
    }
}
