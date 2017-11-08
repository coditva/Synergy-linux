#ifndef CONFIG_H
#define CONFIG_H

/* the host and port to be used for connection */
#define PORT 3020
#define HOST "127.0.0.1"

/* a number which is sent with every request from other devices */
#define SPECIALNUM 49267

/* maximum connections waiting for server */
#define BACKLOG 10

/* size of hash for device id */
#define HASHSIZE 65

/* a key for the hash */
#define HASHKEY "thisIsASuperSecretKey"

/* maximum simultaneous devices */
#define MAXDEVS 5

/* maximum length of device name */
#define MAXNAME 100

#endif /* end of include guard: CONFIG_H */
