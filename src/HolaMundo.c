#include <string.h>
#include <stdio.h>
#include "SudokuView.h"
#include "Socket.h"

int main(int argc, char *argv[]) {
  char mode[20];
  memcpy(mode, argv[1], strlen(argv[1]) + 1);
  Socket_t socket;
  socket_create(&socket);
  if (strcmp(mode, "server") == 0) {
    printf("server\n");
    socket_bind(&socket, "7777");
    socket_listen(&socket, 20);
    socket_accept(&socket);
  }
  if (strcmp(mode, "client") == 0) {
    printf("client\n");
    socket_connect(&socket,"localhost","7777");
  }
  socket_destroy(&socket);
  return 0;
}

