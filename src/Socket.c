#define _POSIX_C_SOURCE 200112L

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

void socket_create(Socket_t *self, const char *service) {
    struct addrinfo hints, *ai_list, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    int s = getaddrinfo(NULL, service, &hints, &ai_list);
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        exit(-1);
    }
    bool connected = false;
    for (ptr = ai_list; ptr != NULL && !connected; ptr = ptr->ai_next) {
        self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (bind(self->fd, ptr->ai_addr, ptr->ai_addrlen) == -1) {
            printf("Error en bindn");
            exit(-1);
        }
    }
    if (listen(self->fd, 20) == -1) {
        printf("Error en listen");
        exit(-1);
    }
    printf("Se conecto bien");
    freeaddrinfo(ai_list);
}

int socket_connect(Socket_t *self, const char *host, const char *service) {
    struct addrinfo hints, *ai_list, *ptr;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int s = getaddrinfo(0, service, &hints, &ai_list);
    if (s != 0) {
        printf("Error in getaddrinfo: %s\n", gai_strerror(s));
        return 1;
    }
    bool connected = false;
    for (ptr = ai_list; ptr != NULL && !connected; ptr = ptr->ai_next) {
        self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int res = connect(self->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (res == -1) {
            perror("ERROR");
            close(self->fd);
        }
        connected = (s != -1);
    }
    printf("Se conecto bien");
    freeaddrinfo(ai_list);
    return 0;
}

int socket_bind(Socket_t *self) {
    return 0;
}

int socket_listen(Socket_t *self, const char *service);

int socket_send(Socket_t *self, const void *buf, const size_t size);

int socket_receive(Socket_t *self);

void socket_destroy(Socket_t *self) {
    close(self->fd);
}

