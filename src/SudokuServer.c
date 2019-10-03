#include <stdio.h>
#include <netinet/in.h>
#include "SudokuServer.h"
#include "Socket.h"
#include "ServerResponse.h"

int sudokuServerStart(SudokuServer_t *self, const char *port) {
  if (sudokuStart(&self->sudoku) != 0) {
    return 1;
  }
  socketCreate(&self->socket);
  if (socketBind(&self->socket, port) == 1) {
    printf("Uso: ./tp server %s\n", port);
    return 1;
  }
  if (socketListen(&self->socket, 20) == 1) {
    printf("[ERROR] sudokuServerStart: ERROR EN LISTEN");
    return 1;
  }
  if (socketAccept(&self->socket, &self->accept_socket) == 1) {
    printf("[ERROR] sudokuServerStart: ERROR EN ACCEPT");
    return 1;
  }
  return 0;
}

int sudokuServerAlive(SudokuServer_t *self) {
  int res_1 = 0;
  int res_2 = 0;
  char command = 0;
  char params[3] = {0};
  if (socketReceive(&self->accept_socket, &command, 1) == 2) {
    return 2;
  }
  if (command == 'P') {
    if (socketReceive(&self->accept_socket, params, 3) == 2) {
      return 2;
    }
  }
  Response_t response;
  responseCreate(&response, command, &params[0], &self->sudoku);
  uint32_t size = htonl(response.size);
  res_1 = socketSend(&self->accept_socket, (char *) &size, 4);
  res_2 = socketSend(&self->accept_socket, response.message, response.size);
  if (res_1 == 1 || res_2 == 1) {
    responseDestroy(&response);
    return 1;
  }
  responseDestroy(&response);
  return 0;
}

void sudokuServerStop(SudokuServer_t *self) {
  sudokuExit(&self->sudoku);
  socketDestroy(&self->accept_socket);
  socketDestroy(&self->socket);
}
