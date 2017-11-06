#ifndef DEVICE_H
#define DEVICE_H

void device_new(char *device_info);
void device_pair(int devicefd);
void device_connect(char *device_info);

#endif /* end of include guard: DEVICE_H */
