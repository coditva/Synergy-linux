#include <stdio.h>

#include "device.h"

void device_new(char *device_info)
{
    printf("NEW: %s\n", device_info);
}

void device_pair(char *device_msg)
{
    printf("PAIR: %s\n", device_msg);
}
