#include <stdlib.h>
#include <string.h>
#include "ServerResponse.h"

/*
 * Arma la representacion del sudoku, obteniendola
 * cuando ejecuta un comando get.
 */
static void __getBoardView(Response_t *self, Sudoku_t *sudoku) {
  self->size = 722;
  sudokuGet(sudoku, &self->message);
}

/*
 * Clase que configura el tamanio y el mensaje
 * del response, dependiendo de un mensaje
 * pasado por parametro.
 */
static void __getSudokuMessage(Response_t *self, const char *message) {
  self->message = (char *) malloc(sizeof(char) * strlen(message));
  self->size = strlen(message);
  memcpy(self->message, message, strlen(message));
}

/*
 * Funcion auxiliar que chequea los parametros
 * en el caso de que la funcion sea put, para luego
 * realizar la operacion correspondiente en
 * el sudoku.
 */
static void __evaluatePutParameters(Response_t *self,
                                  char *params,
                                  Sudoku_t *sudoku) {
  uint8_t row = params[0] - '0';
  uint8_t column = params[1] - '0';
  uint8_t value = params[2] - '0';
  const char *messagePut = sudokuPut(sudoku,
                                     (int) value,
                                     (int) row,
                                     (int) column);
  if (strcmp(messagePut, "OK\n") == 0) {
    __getBoardView(self, sudoku);
  } else {
    __getSudokuMessage(self, messagePut);
  }
}

void responseCreate(Response_t *self,
                    char command,
                    char *params,
                    Sudoku_t *sudoku) {
  if (command == 'G') {
    __getBoardView(self, sudoku);
  }
  if (command == 'P') {
    __evaluatePutParameters(self, params, sudoku);
  }
  if (command == 'V') {
    const char *messageVerify = sudokuVerify(sudoku);
    __getSudokuMessage(self, messageVerify);
  }
  if (command == 'R') {
    sudokuReset(sudoku);
    __getBoardView(self, sudoku);
  }
}

void responseDestroy(Response_t *self) {
  free(self->message);
}



