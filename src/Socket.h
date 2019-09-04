#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct {
  int fd;
} Socket_t;

void socket_create(Socket_t *self);
int socket_connect(Socket_t *self, const char *host, const char *service);
int socket_bind(Socket_t *self);
int socket_listen(Socket_t *self, const char *service);
int socket_send(Socket_t *self, const void *buf, const size_t size);
int socket_receive(Socket_t *self);
void socket_destroy(Socket_t *self);

#endif