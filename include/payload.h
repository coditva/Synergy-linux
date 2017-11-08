#ifndef PAYLOAD_H
#define PAYLOAD_H

payload_t * payload_get(int);
void payload_send(int, payload_t *);
payload_t * payload_create(char *, enum message_type, char *);

#endif /* end of include guard: PAYLOAD_H */
