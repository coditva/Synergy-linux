#include <unistd.h>
#include <netinet/ip.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "config.h"
#include "datatypes.h"

int main(int argc, char *argv[])
{
    int sockfd, connfd;
    struct sockaddr_in addr;                        /* socket config */
    struct sockaddr peer_addr;                      /* peer details */
    socklen_t peer_addr_size;
    message_t buffer;
    
    /* create a socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* put info in addr about the socket */
    bzero(&addr, sizeof(struct sockaddr_in));       /* clear it */
    addr.sin_family = AF_INET;                      /* always to AF_INET */
    addr.sin_port   = htons(PORT);                  /* set port */
    addr.sin_addr.s_addr = inet_addr(HOST);         /* set the host */

    /* connect to the server */
    connect(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));

    while (1) {
        scanf("%s", buffer.message);
        buffer.special_num = SPECIALNUM;
        buffer.type = MT_HELLO;
        write(sockfd, &buffer, sizeof(message_t));
        buffer.type = MT_NEW;
        strcpy(buffer.message, "Register this new device");
        write(sockfd, &buffer, sizeof(message_t));
    }
}
