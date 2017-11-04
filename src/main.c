#include <stdio.h>

#include "server.h"

int main(int argc, char *argv[])
{
    server_init();
    server_accept();
    return 0;
}
