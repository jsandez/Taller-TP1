#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>
#include "SudokuClient.h"
#include "Socket.h"
#include "ClientCommands.h"

/*
 * Funcion que lee caracteres desde stdin y los codifica.
 * Return:  1 si se tiene que cerrar el juego correctamente
 *          El valor que devuelve decode
 */
static int getInput(char command[5]) {
  char message[20] = {0}, c;
  int i = 0;
  while ((c = fgetc(stdin)) != '\n') {
    if (c == EOF)
      return 1;
    message[i] = c;
    i++;
  }
  message[i] = '\0';
  return decode(message, command);
}

/*
 * Loop que verifica los comandos que ingresa el cliente.
 * Status: 0: comando correcto
 *         1: se cerro el juego con exit o EOF
 */
static int getCommandLoop(char *command) {
  int command_result = getInput(command);
  while (command_result != 0) {
    if (command_result == 1) {
      return 1;
    }
    if (command_result == 2) {
      command_result = getInput(command);
    }
  }
  return 0;
}

/*
 * Funcion que devuelve el tamanio del buffer que recibe el socket.
 * Es la primer llamada a recv para determinar el tamanio de nuestro
 * segundo mensaje a leer.
 * Return: Lo que devuelva recv si no es 0
 *         Tamanio del buffer que se debe leer en la proxima llamada
 */
static uint32_t readSize(Socket_t *socket) {
  int res = 0;
  char buffer_msg_size[4] = {0};
  uint32_t size_of_message = 0;
  res = socketReceive(socket, buffer_msg_size, 4);
  if (res == 2) {
    return res;
  }
  memcpy(&size_of_message, buffer_msg_size, sizeof(uint32_t));
  return size_of_message;
}

/*
 * Inicia el cliente conectandose a un host y puerto especificado.
 * Return: 0 si se conecto bien
 *         1 si no pudo conectarse
 */
int sudokuClientStart(SudokuClient_t *self,
                      const char *host,
                      const char *port) {
  self->socket = (Socket_t *) malloc(sizeof(Socket_t));
  socketCreate(self->socket);
  if (socketConnect(self->socket, host, port) == 1) {
    printf("Uso: ./tp client %s %s\n", host, port);
    return 1;
  }
  return 0;
}

/*
 * Ciclo de vida de juego del sudoku, del lado del cliente
 * Retorna: 0 si se debe seguir jugando
 *          1 si se quiere cerrar el juego
 *          Lo que devuelva send
 *          Lo que devuelva recv
 */
int sudokuClientPlay(SudokuClient_t *self) {
  int res = 0;
  char command[5] = {0};
  if (getCommandLoop(command)) {
    return 1;
  }
  res = socketSend(self->socket, command, 5);
  if (res != 0) {
    return res;
  }
  uint32_t size_of_message = readSize(self->socket);
  if (size_of_message == 1 || size_of_message == 2) {
    return size_of_message;
  }
  uint32_t msg_size = ntohl(size_of_message);
  char *buffer_msg = malloc(sizeof(char) * (msg_size + 1));
  res = socketReceive(self->socket, buffer_msg, msg_size);
  if (res != 0) {
    free(buffer_msg);
    return res;
  }
  printf("%s", buffer_msg);
  free(buffer_msg);
  return 0;
}

/*
 * Libera los recursos del cliente
 */
void sudokuClientStop(SudokuClient_t *self) {
  socketDestroy(self->socket);
  free(self->socket);
}
