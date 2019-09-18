#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>
#include "SudokuClient.h"
#include "Socket.h"

static int __evaluatePut(SudokuClient_t *self, const char *stdIn) {
  int row,column,value;
  int res = sscanf(stdIn, "put %i in %i,%i", &value, &row, &column);
  if (res != 3) {
    return 1;
  } else {
    if (row < 1 || row > 9 || column < 1 || column > 9) {
      fprintf(stderr, "Error en los índices. Rango soportado: [1,9]\n");
      return 2;
    }
    if (value < 1 || value > 9) {
      fprintf(stderr, "Error en el valor ingresado. Rango soportado: [1,9]\n");
      return 2;
    }
    res = socketSend(&self->socket, "P", 1);
    if (res != 0) {
      return res;
    }
    char params[] = {(char) row + '0', (char) column + '0', (char) value + '0'};
    res = socketSend(&self->socket, params, 3);
    return res;
  }
}

/*
 * Funcion que decodifica lo que se va a leer desde stdIn.
 * Devuelve: 0 si el comando es correcto
 *           1 si quiere salir del juego
 *           2 si es incorrecto. Se deja el stdIn abierto para
 *           que ingrese otro
 */
static int __decode(SudokuClient_t *self, char *stdIn) {
  int result = 0;
  result = __evaluatePut(self, stdIn);
  if (result != 1) {
    return result;
  }
  if (!strncmp(stdIn, "verify", 6)) {
    result = socketSend(&self->socket, "V", 1);
    return result;
  }
  if (!strncmp(stdIn, "reset", 5)) {
    result = socketSend(&self->socket, "R", 1);
    return result;
  }
  if (!strncmp(stdIn, "get", 3)) {
    result = socketSend(&self->socket, "G", 1);
    return result;
  }
  if (!strncmp(stdIn, "exit", 4)) {
    return 1;
  }
  return 2;
}

/*
 * Funcion que lee caracteres desde stdin y los codifica.
 * Return:  1 si se tiene que cerrar el juego correctamente
 *          El valor que devuelve decode
 */
static int __getInput(SudokuClient_t *self) {
  char message[20] = {0};
  if (fgets(message, 20, stdin) == NULL) {
      return 1;
  }
  return __decode(self, message);
}

/*
 * Loop que verifica los comandos que ingresa el cliente.
 * Status: 0: comando correcto
 *         1: se cerro el juego con exit, EOF, o nos cerraron la conexion
 */
static int __sendCommandLoop(SudokuClient_t *self) {
  int command_result = __getInput(self);
  while (command_result != 0) {
    if (command_result == 1) {
      return 1;
    }
    if (command_result == 2) {
      command_result = __getInput(self);
    }
  }
  return 0;
}

/*
 * Funcion que devuelve el tamanio del buffer que recibe el socket.
 * Es la primer llamada a recv para determinar el tamanio de nuestro
 * segundo mensaje a leer.
 * Return: 0 si no hubo problemas
 *         Lo que devuelva socketReceive si surgio algo
 */
static int __readSize(Socket_t *socket, uint32_t *size_of_message) {
  char buffer_msg_size[4] = {0};
  int res = socketReceive(socket, buffer_msg_size, 4);
  if (res == 2) {
    return res;
  }
  memcpy(size_of_message, buffer_msg_size, sizeof(uint32_t));
  *size_of_message = ntohl(*size_of_message);
  return 0;
}

/*
 * Inicia el cliente conectandose a un host y puerto especificado.
 * Return: 0 si se conecto bien
 *         1 si no pudo conectarse
 */
int sudokuClientStart(SudokuClient_t *self,
                      const char *host,
                      const char *port) {
  socketCreate(&self->socket);
  if (socketConnect(&self->socket, host, port) == 1) {
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
  if (__sendCommandLoop(self)) {
    return 1;
  }
  uint32_t msg_size = 0;
  int res = __readSize(&self->socket, &msg_size);
  if (res == 1 || res == 2) {
    return res;
  }
  char *buffer_msg = malloc(sizeof(char) * (msg_size + 1));
  res = socketReceive(&self->socket, buffer_msg, msg_size);
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
  socketDestroy(&self->socket);
}
