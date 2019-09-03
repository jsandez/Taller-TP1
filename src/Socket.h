#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct {
  int fd;
} socket_t;

void socket_init(socket_t *self);
int socket_connect(socket_t *self, const char *host, const char *service, int port);
int socket_bind(socket_t *self);
int socket_listen(socket_t *self, const char *service);
int socket_send(socket_t *self, const void *buf, const size_t size);
int socket_receive(socket_t *self);
void socket_release(socket_t *self);

#endif