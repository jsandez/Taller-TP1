#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <stdbool.h>
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

void socketCreate(Socket_t *self) {
  self->fd = -1;
}

int socketConnect(Socket_t *self, const char *host, const char *service) {
  struct addrinfo *ai_list, *ptr;
  if (socket_getaddrinfo(&ai_list, host, service, 0) != 0) {
    return 1;
  }
  bool connected = false;
  for (ptr = ai_list; ptr != NULL && !connected; ptr = ai_list->ai_next) {
    self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (connect(self->fd, ptr->ai_addr, ptr->ai_addrlen) == -1) {
      close(self->fd);
      freeaddrinfo(ai_list);
      return 1;
    }
    connected = true;
  }
  freeaddrinfo(ai_list);
  return 0;
}

int socketBind(Socket_t *self, const char *service) {
  struct addrinfo *ai_list, *ptr;
  if (socket_getaddrinfo(&ai_list, NULL, service, 0) != 0) {
    return 1;
  }
  bool is_bind = false;
  for (ptr = ai_list; ptr != NULL && !is_bind; ptr = ai_list->ai_next) {
    self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (bind(self->fd, ptr->ai_addr, ptr->ai_addrlen) == -1) {
      close(self->fd);
      freeaddrinfo(ai_list);
      return 1;
    }
    is_bind = true;
  }
  freeaddrinfo(ai_list);
  return 0;
}

int socketListen(Socket_t *self, int waiting_clients) {
  if (listen(self->fd, waiting_clients) == -1) {
    close(self->fd);
    return 1;
  }
  return 0;
}

int socketAccept(Socket_t *self, Socket_t *accept_socket) {
  int newFD = accept(self->fd, NULL, NULL);
  if (newFD == -1) {
    close(self->fd);
    return 1;
  }
  int val = 1;
  setsockopt(newFD, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
  accept_socket->fd = newFD;
  return 0;
}

int socketSend(Socket_t *self, const char *buf,int length) {
  int bytes_send = 0;
  bool connected = true;
  while (bytes_send < length && connected) {
    int valread = send(self->fd, &buf[bytes_send], length - bytes_send, MSG_NOSIGNAL);
    if (valread > 0) {
      bytes_send += valread;
    } else {
      printf("[ERROR] socketSend: %s\n", strerror(errno));
      close(self->fd);
      connected = false;
    }
  }
  printf("Message sent\n");
  return 0;
}

int socketReceive(Socket_t *self, char *buf, int length) {
  int bytes_recv = 0;
  bool connected = true;
  while (bytes_recv < length && connected) {
    int valrecv = recv(self->fd, &buf[bytes_recv], length - bytes_recv -1, 0);
    if (valrecv == -1) {
      printf("[ERROR] socketSend: %s\n", strerror(errno));
      close(self->fd);
      connected = false;
    }
    if (valrecv > 0) {
      buf[valrecv] = 0;
      bytes_recv = valrecv;
    } else {
      break;
    }
  }
  printf("Message receive\n");
  return 0;
}

int socketShutdown(Socket_t *self) {
  shutdown(self->fd, SHUT_RDWR);
}

void socketDestroy(Socket_t *self) {
  close(self->fd);
}

