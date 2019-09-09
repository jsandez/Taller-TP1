#include <stdio.h>
#include <netinet/in.h>
#include "SudokuServer.h"
#include "Socket.h"
#include "Response.h"

int sudokuServerStart(SudokuServer_t *self, const char *port) {
  self->socket = (Socket_t *) malloc(sizeof(Socket_t));
  socketCreate(self->socket);
  if (socketBind(self->socket, port) == 1) {
    printf("Uso: ./tp server %s\n", port);
    return 1;
  }
  socketListen(self->socket, 20);
  //Socket_t accept_socket;
  self->accept_socket = (Socket_t *) malloc(sizeof(Socket_t));
  socketAccept(self->socket, self->accept_socket);
  /*else {
    res = socketListen(self->socket, 20);
    //Socket_t accept_socket;
    self->accept_socket = (Socket_t *) malloc(sizeof(Socket_t));
    res = socketAccept(self->socket, self->accept_socket);
    res = socketReceive(self->accept_socket, bufferRecv, 1024);
    //const char *asd = strcat("Mandaste esto ", bufferRecv);
    char bufferResponse[727] = {0};
    evaluateCommand(bufferRecv, bufferResponse);
    char buffer_size[4];
    for (int i = 0; i < 4; i++) {
      buffer_size[i] = bufferResponse[i];
    }
    char second_buffer[723];
    for (int i = 0; i < 723; i++) {
      second_buffer[i] = bufferResponse[i + 4];
    }
    res = socketSend(self->accept_socket, buffer_size, 4);
    res = socketSend(self->accept_socket, second_buffer, 1024);
  }*/
  return 0;
}

int sudokuServerAlive(SudokuServer_t *self) {
  int res = 0;
  char bufferRecv[5]= {0};
  res = socketReceive(self->accept_socket, bufferRecv, 5);
  //const char *asd = strcat("Mandaste esto ", bufferRecv);
  Response_t response;
  responseCreate(&response,bufferRecv);
  /*char *bufferResponse;
  evaluateCommand(bufferRecv, bufferResponse);
  char buffer_size[4];
  for (int i = 0; i < 4; i++) {
    buffer_size[i] = bufferResponse[i];
  }
  //char *second_buffer = malloc(sizeof(char) * 726);
  for (int i = 0; i < 722; i++) {
    second_buffer[i] = bufferResponse[i + 4];
  }*/

  res = socketSend(self->accept_socket, response.size, 4);
  res = socketSend(self->accept_socket, response.message, 722);
  responseDestroy(&response);
  return res;
}

void sudokuServerStop(SudokuServer_t *self) {
  socketDestroy(self->accept_socket);
  socketDestroy(self->socket);
  free(self->accept_socket);
  free(self->socket);
}
