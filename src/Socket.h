#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdlib.h>

typedef struct {
    int fd;
} Socket_t;

void socket_create(Socket_t *self);

int socket_connect(Socket_t *self, const char *host, const char *service);

int socket_bind(Socket_t *self, const char *service);

int socket_listen(Socket_t *self, int waiting);

int socket_accept(Socket_t *self,Socket_t *accept_socket);

int socket_send(Socket_t *self, const char *buf);

int socket_receive(Socket_t *self, char *buf);

void socket_destroy(Socket_t *self);

#endif

