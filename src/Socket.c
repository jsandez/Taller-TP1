#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "Socket.h"

static int socket_getaddrinfo(struct addrinfo **ai_list, const char *host, const char *service, int flags) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = flags;
  int res = getaddrinfo(host, service, &hints, ai_list);
  return res;
}

void socket_create(Socket_t *self) {
  self->fd = -1;
}

int socket_connect(Socket_t *self, const char *host, const char *service) {
  struct addrinfo *ai_list, *ptr;
  int res = socket_getaddrinfo(&ai_list, host, service, 0);
  if (res != 0) {
    printf("[ERROR] socket_connect: %s\n", gai_strerror(res));
    return 1;
  }
  bool connected = false;
  for (ptr = ai_list; ptr != NULL && !connected; ptr = ai_list->ai_next) {
    self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    res = connect(self->fd, ptr->ai_addr, ptr->ai_addrlen);
    if (res != 0) {
      printf("[ERROR] socket_connect: %s\n", strerror(errno));
      close(self->fd);
      freeaddrinfo(ai_list);
      return 1;
    }
    connected = true;
  }
  freeaddrinfo(ai_list);
  return 0;
}

int socket_bind(Socket_t *self, const char *service) {
  struct addrinfo *ai_list, *ptr;
  int res = socket_getaddrinfo(&ai_list, NULL, service, 0);
  if (res != 0) {
    printf("[ERROR] socket_bind: %s\n", gai_strerror(res));
    return 1;
  }
  bool is_bind = false;
  for (ptr = ai_list; ptr != NULL && !is_bind; ptr = ai_list->ai_next) {
    self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    res = bind(self->fd, ptr->ai_addr, ptr->ai_addrlen);
    if (res != 0) {
      printf("[ERROR] socket_bind: %s\n", strerror(errno));
      close(self->fd);
      freeaddrinfo(ai_list);
      return 1;
    }
    is_bind = true;
  }
  freeaddrinfo(ai_list);
  return 0;
}

int socket_listen(Socket_t *self, int waiting) {
  int res = listen(self->fd, waiting);
  if (res != 0) {
    printf("[ERROR] socket_listen: %s\n", strerror(errno));
    close(self->fd);
    return 1;
  }
  return 0;
}

int socket_accept(Socket_t *self, Socket_t *accept_socket) {
  int newFD = accept(self->fd, NULL, NULL);
  if (newFD == -1) {
    printf("[ERROR] socket_accept: %s\n", strerror(errno));
    close(self->fd);
    return 1;
  }
  accept_socket->fd = newFD;
  return 0;
}

int socket_send(Socket_t *self, const void *buf) {
  int valread = send(self->fd, buf, 1024, 0);
  if (valread == -1) {
    printf("[ERROR] socket_send: %s\n", strerror(errno));
    close(self->fd);
    return 1;
  }
  printf("Message sent\n");
  return 0;
}

int socket_receive(Socket_t *self, void *buf) {
  int valrecv = recv(self->fd, buf, 1024, 0);
  if (valrecv == -1) {
    printf("[ERROR] socket_send: %s\n", strerror(errno));
    close(self->fd);
    return 1;
  }
  printf("%s\n", (char *) buf);
  printf("Message receive\n");
  return 0;
}

void socket_destroy(Socket_t *self) {
  close(self->fd);
}

