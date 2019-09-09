#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdlib.h>

typedef struct {
  int fd;
} Socket_t;

void socketCreate(Socket_t *self);

int socketConnect(Socket_t *self, const char *host, const char *service);

int socketBind(Socket_t *self, const char *service);

int socketListen(Socket_t *self, int waiting_clients);

int socketAccept(Socket_t *self, Socket_t *accept_socket);

int socketSend(Socket_t *self, const char *buf,int length);

int socketReceive(Socket_t *self, char *buf,int length);

int socketShutdown(Socket_t *self);

void socketDestroy(Socket_t *self);

#endif

