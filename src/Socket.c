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

static void socket_getaddrinfo(struct addrinfo **ai_list, const char *host, const char *service, int flags) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = flags;
    int s = getaddrinfo(host, service, &hints, ai_list);
    if (s != 0) {
        printf("[ERROR] socket_getaddrinfo: %s\n", gai_strerror(s));
        exit(-1);
    }
}

void socket_create(Socket_t *self) {
    self->fd = -1;
}

int socket_connect(Socket_t *self, const char *host, const char *service) {
    struct addrinfo *ai_list, *ptr;
    char buffer[1024] = {0};
    socket_getaddrinfo(&ai_list, host, service, 0);
    bool we_are_connected = false;
    for (ptr = ai_list; ptr != NULL && !we_are_connected; ptr = ai_list->ai_next) {
        self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int res = connect(self->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (res != 0) {
            printf("Error: %s\n", strerror(errno));
            close(self->fd);
            freeaddrinfo(ai_list);
            return res;
        }
        we_are_connected = true;
    }
    send(self->fd, "hello im the client\n", strlen("hello im the client\n"), 0);
    printf("Hello message sent\n");
    int valread = read(self->fd, buffer, 1024);
    printf("valread %i\n", valread);
    printf("%s\n", buffer);
    freeaddrinfo(ai_list);
    return 0;
}

int socket_bind(Socket_t *self, const char *service) {
    struct addrinfo *ai_list, *ptr;
    socket_getaddrinfo(&ai_list, NULL, service, 0);
    bool is_bind = false;
    for (ptr = ai_list; ptr != NULL && !is_bind; ptr = ai_list->ai_next) {
        self->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        int res = bind(self->fd, ptr->ai_addr, ptr->ai_addrlen);
        if (res != 0) {
            printf("Error: %s\n", strerror(errno));
            close(self->fd);
            freeaddrinfo(ai_list);
            return res;
        }
        is_bind = true;
    }
    freeaddrinfo(ai_list);
    return 0;
}

int socket_listen(Socket_t *self, int waiting) {
    int res = listen(self->fd, waiting);
    if (res != 0) {
        printf("Error: %s\n", strerror(errno));
        close(self->fd);
    }
    return res;
}

int socket_accept(Socket_t *self) {
    int newFD = accept(self->fd, NULL, NULL);
    char buffer[1024] = {0};
    if (newFD < 0) {
        printf("Error: %s\n", strerror(errno));
        close(self->fd);
    }
    int valread = read( newFD , buffer, 1024);
    printf("valread = %i\n",valread);
    printf("%s\n",buffer );
    send(newFD , "hello im the server\n" , strlen("hello im the server\n") , 0 );
    printf("Hello message sent\n");
    newFD = self->fd;
    return newFD;
}

int socket_send(Socket_t *self, const void *buf, const size_t size) {
    int valread = send(self->fd, buf, strlen(buf), 0);
    printf("valread = %i\n", valread);
    printf("%s\n", buf);
    printf("Message sent\n");
    return valread;
}

int socket_receive(Socket_t *self,const void *buf, const size_t size) {
    int valread = read(self->fd, buf, size);
    printf("valread = %i\n", valread);
    printf("%s\n", buf);
    printf("Message receive\n");
    return valread;
}

void socket_destroy(Socket_t *self) {
    close(self->fd);
}

