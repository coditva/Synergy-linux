#ifndef DEVICE_H
#define DEVICE_H

/* pair a device */
device_t * device_pair(char *device_name, payload_t *payload);

/* return device info for a device id */
device_t * device_get(char *device_id);

#endif /* end of include guard: DEVICE_H */
