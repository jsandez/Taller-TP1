#include <stdio.h>
#include "SudokuServer.h"
#include "Socket.h"
#include "ServerResponse.h"

/*
 * Inicia el servidor en un puerto especificado
 * Devuelve:0 si se inicio correctamente
 *          1 si el puerto es incorrect, si hay error en el listen o en el accept
 */
int sudokuServerStart(SudokuServer_t *self, const char *port) {
  self->socket = (Socket_t *) malloc(sizeof(Socket_t));
  socketCreate(self->socket);
  if (socketBind(self->socket, port) == 1) {
    printf("Uso: ./tp server %s\n", port);
    return 1;
  }
  if (socketListen(self->socket, 20) == 1) {
    printf("[ERROR] sudokuServerStart: ERROR EN LISTEN");
    return 1;
  }
  self->accept_socket = (Socket_t *) malloc(sizeof(Socket_t));
  if (socketAccept(self->socket, self->accept_socket) == 1) {
    printf("[ERROR] sudokuServerStart: ERROR EN ACCEPT");
    return 1;
  }
  return 0;
}

/*
 * Ciclo de vida del sudoku del lado del servidor
 * Devuelve: 0 si se tiene que seguir ejecutando
 *           1 si hubo algun error
 *           2 si se cerro el servidor del lado del cliente
 */
int sudokuServerAlive(SudokuServer_t *self) {
  int res_1 = 0;
  int res_2 = 0;
  int res_3 = 0;
  char bufferRecv[5] = {0};
  if (socketReceive(self->accept_socket, bufferRecv, 5) == 2) {
    return 2;
  }
  Response_t response;
  responseCreate(&response, bufferRecv);
  res_2 = socketSend(self->accept_socket, response.size, 4);
  res_3 = socketSend(self->accept_socket, response.message, response.size_int);
  if (res_1 == 1 || res_2 == 1 || res_3 == 1) {
    responseDestroy(&response);
    return 1;
  }
  responseDestroy(&response);
  return 0;
}

/*
 * Libera los recursos del servidor
 */
void sudokuServerStop(SudokuServer_t *self) {
  socketDestroy(self->accept_socket);
  socketDestroy(self->socket);
  free(self->accept_socket);
  free(self->socket);
}
