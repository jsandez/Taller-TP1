#include <string.h>
#include <stdio.h>
#include "SudokuView.h"
#include "Socket.h"

int main(int argc, char *argv[]) {
  /*char mode[20];
  int res = 0;
  Socket_t socket;
  socket_create(&socket);
  memcpy(mode, argv[1], strlen(argv[1]) + 1);
  if (strcmp(mode, "server") == 0) {
    const char *port = argv[2];
    char buffer[1024] = {0};
    printf("server\n");
    res = socket_bind(&socket, port);
    res = socket_listen(&socket, 20);
    Socket_t accept_socket;
    res = socket_accept(&socket, &accept_socket);
    res = socket_receive(&accept_socket, buffer);
    res = socket_send(&accept_socket, "hola soy el server");
    socket_destroy(&accept_socket);
  } else {
    if (strcmp(mode, "client") == 0) {
      char buffer[1024] = {0};
      const char *host = argv[2];
      const char *port = argv[3];
      printf("client\n");
      res = socket_connect(&socket, host, port);
      res = socket_send(&socket, "hola soy el cliente");
      res = socket_receive(&socket, buffer);
    } else {
      printf("ERROR DE PARAMETROS");
      res = 1;
    }
  }
  socket_destroy(&socket);
  return res;*/
  Board_t board;
  boardCreate(&board, "board.txt");
  printBoard(&board);
  printf("\n");
  boardPut(&board,2,2,3);
  printBoard(&board);
  printf("\n");
  boardReset(&board);
  printBoard(&board);
  printf("\n");
  boardDestroy(&board);

}

