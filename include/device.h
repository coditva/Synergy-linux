#ifndef DEVICE_H
#define DEVICE_H

void device_new(char *device_info);
void device_pair(int devicefd);
void device_connect(char *device_info);
device_t * device_get(char *device_id);

#endif /* end of include guard: DEVICE_H */
