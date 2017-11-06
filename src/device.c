#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "datatypes.h"
#include "device.h"

void device_new(char *device_info)
{
    printf("NEW: %s\n", device_info);
}

void device_pair(int devicefd)
{
    message_t buffer;

    /* ask if want to pair */

    /* TODO: generate a hash */
    char hash[] = "thisissomehash";

    char filename[200] = "synergy/devices/";
    strcat(filename, hash);

    /* TODO: save it in assoc with the device */
    mkdir("synergy/devices", S_IRWXU | S_IRGRP | S_IROTH);

    /* create a device for it */
    int fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR);
    if (fd == -1) { printf("Device exists\n"); }
    char msg[] = "DEVICE INFO TO BE STORED\n";
    write(fd, msg, sizeof(msg));
    close(fd);

    /* send it back */
    strcpy(buffer.message, hash);
    write(devicefd, &buffer, sizeof(message_t));
}

void device_connect(char *device_info)
{
    printf("CONNECT: %s\n", device_info);
}
