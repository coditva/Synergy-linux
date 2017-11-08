#ifndef DEVICE_H
#define DEVICE_H

/* pair a device */
device_t * device_pair(char *device_name, payload_t *payload);

/* return device info for a device name */
device_t * device_get(char *device_name);

#endif /* end of include guard: DEVICE_H */
