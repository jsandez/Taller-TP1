#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Socket.h"
#include <netdb.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void socket_init(socket_t *self) {
  int socketFd = socket(AF_INET, SOCK_STREAM, 0);
  self->fd = socketFd;
}

int socket_connect(socket_t *self, const char *host, const char *service, int port) {
  struct addrinfo hints, *ai_list, *ptr;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  int s = getaddrinfo(host, service, &hints, &ai_list);
  if (s != 0) {
    printf("Error in getaddrinfo: %s\n", gai_strerror(s));
    return 1;
  }
  bool connected = false;
  for (ptr = ai_list; ptr != NULL && !connected; ptr = ptr->ai_next) {
    self = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    int res = connect(self, ptr->ai_addr, ptr->ai_addrlen);
    if (res != 0) {
      perror("ERROR");
      close(self);
    }
    connected = (s != -1);
  }
  int res = connect(self->fd, (struct sockaddr *) &ip4addr, sizeof ip4addr);
  if (res) {
    perror("Hubo un error en connect");
  }
  printf("Se conecto bien");
  freeaddrinfo(ai_list);
  return 0;
}
int socket_bind(socket_t *self);
int socket_listen(socket_t *self, const char *service);
int socket_send(socket_t *self, const void *buf, const size_t size);
int socket_receive(socket_t *self);

void socket_release(socket_t *self) {
  close(self->fd);
}