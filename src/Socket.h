#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct Socket {
  int fd;
} socket_t;

int socket_send(socket_t *self, const void *buf, const size_t size);
int socket_receive();
void socket_init(socket_t *socket);
void socket_release(socket_t *socket);
void socket_connect(socket_t *socket, const char *host, const char *service);
int socket_bind(socket_t *socket);
int socket_listen(socket_t *socket, const char *service);

#endif