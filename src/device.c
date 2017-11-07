#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "config.h"
#include "datatypes.h"
#include "device.h"

/*
 * Creates a file in /devices with a generated device id. Does nothing if
 * already paired
 * @param int devicefd file descriptor for the device
 */
void device_pair(int devicefd)
{
    message_t buffer;
    device_t device;
    char filename[20 + HASHSIZE] = "synergy/devices/";
    int fd;

    /* TODO: generate a hash */
    device.id = (char *) malloc(HASHSIZE);
    strcpy(device.id, "thisissomeverybighashusedasdeviceid");

    strcat(filename, device.id);

    /* save it in assoc with the device */
    mkdir("synergy/devices", S_IRWXU | S_IRGRP | S_IROTH);

    /* create a device for it */
    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR);
    if (fd == -1) {
        printf("Device exists\n");
    } else {
        write(fd, &device, sizeof(device_t));
        close(fd);
    }

    /* send it back */
    strcpy(buffer.message, device.id);
    write(devicefd, &buffer, sizeof(message_t));
}

/*
 * Reads the file in /devices and returns the device info for the given
 * device id
 * @param char* device_id
 * @return device_t* the device info
 */
device_t * device_get(char *device_id)
{
    device_t *device;
    char filename[200] = "synergy/devices/";
    int devfd;

    if (device_id == NULL || !strcmp(device_id, "")) {
        return NULL;
    }
    strcat(filename, device_id);

    /* check if it can be opened */
    devfd = open(filename, O_RDONLY);
    if (devfd == -1) {
        return NULL;
    }

    /* load device details */
    device = (device_t *) malloc(sizeof(device_t));
    read(devfd, device, sizeof(device_t));

    close(devfd);
    return device;
}

/*
 * Checks if file with the device id exists and returns 1 if it does and 0
 * otherwise
 * @param char* the device id to be checked for
 * @return int 1 if exists, 0 if not
 */
int device_is_paired(char *device_id)
{
    char filename[200] = "synergy/devices/";
    int devfd;

    if (device_id == NULL || !strcmp(device_id, "")) {
        return 0;
    }
    strcat(filename, device_id);

    devfd = open(filename, O_RDONLY);
    if (devfd == -1) {
        return 0;
    }

    close(devfd);
    return 1;
}
