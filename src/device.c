#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/evp.h>

#include "config.h"
#include "datatypes.h"
#include "device.h"

char * get_random_string(int size);

/*
 * Creates a file in /devices with a generated device id. Does nothing if
 * already paired
 * @param int devicefd file descriptor for the device
 */
device_t * device_pair(char *device_name, payload_t *payload)
{
    device_t *device = NULL;
    char filename[20 + HASHSIZE] = "synergy/devices/";
    devid_t *devid;
    int fd;

    if (device_name == NULL) {
        return NULL;
    }

    device = (device_t *) malloc(sizeof(device_t));

    /* get a hash */
    devid = get_random_string(HASHSIZE);

    /* copy everything to device object */
    strcpy(device -> id, devid);
    strcpy(device -> key, payload -> message.value);
    strcpy(device -> name, device_name);

    free(devid);

    /* create a file named as the device id if not existing */
    mkdir("synergy/devices", S_IRWXU | S_IRGRP | S_IROTH);
    strcat(filename, device_name);
    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, S_IRUSR);

    /* if the device is new, store the device object */
    if (fd == -1) {
        printf("Device exists\n");
    } else {
        write(fd, device, sizeof(device_t));
        close(fd);
    }

    return device;
}

/*
 * Reads the file in /devices and returns the device info for the given
 * device id
 * @param devid_t* device_id
 * @return device_t* the device info
 */
device_t * device_get(char *device_name)
{
    device_t *device;
    char filename[200] = "synergy/devices/";
    int devfd;

    if (device_name == NULL || !strcmp(device_name, "")) {
        return NULL;
    }
    strcat(filename, device_name);

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

char * get_random_string(int size)
{
    char *string = (char *) malloc(size);
    srand(time(NULL));

    for (int i = 0; i < size - 1; ++i) {
        string[i] = 'a' + (rand()%26);
    }
    string[size] = '\0';

    return string;
}
