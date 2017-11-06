#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "config.h"
#include "datatypes.h"
#include "device.h"

void device_new(char *device_info)
{
    printf("NEW: %s\n", device_info);
}

void device_pair(int devicefd)
{
    message_t buffer;
    device_t device;

    /* TODO: ask if want to pair */

    /* TODO: generate a hash */
    device.id = (char *) malloc(HASHSIZE);
    strcpy(device.id, "thisissomeverybighashusedasdeviceid");

    char filename[200] = "synergy/devices/";
    strcat(filename, device.id);

    /* save it in assoc with the device */
    mkdir("synergy/devices", S_IRWXU | S_IRGRP | S_IROTH);

    /* create a device for it */
    int fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR);
    if (fd == -1) { printf("Device exists\n"); }
    write(fd, &device, sizeof(device_t));
    close(fd);

    /* send it back */
    strcpy(buffer.message, device.id);
    write(devicefd, &buffer, sizeof(message_t));
}

void device_connect(char *device_info)
{
    printf("CONNECT: %s\n", device_info);
}

device_t * device_get(char *device_id)
{
    char filename[200] = "synergy/devices/";
    strcat(filename, device_id);
    int devfd = open(filename, O_RDONLY);
    if (devfd == -1) {
        return NULL;
    }
    device_t *device = (device_t *) malloc(sizeof(device_t));
    read(devfd, device, sizeof(device_t));
    return device;
}
