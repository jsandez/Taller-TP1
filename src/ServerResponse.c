#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include "ServerResponse.h"

static void getBoardView(Response_t *self, Sudoku_t *sudoku) {
  self->message = (char *) malloc(722);
  sudokuGet(sudoku, self->message);
  self->size_int = 722;
  uint32_t sizeForChar = htonl(self->size_int);
  memcpy(self->size, &sizeForChar, 4);
}

static void getSudokuMessage(Response_t *self, const char *message) {
  size_t length = strlen(message);
  self->message = (char *) malloc(sizeof(char) * length);
  self->size_int = length;
  uint32_t sizeForChar = htonl(self->size_int);
  memcpy(self->size, &sizeForChar, 4);
  memcpy(self->message, message, length);
}

static void evaluatePutParameters(Response_t *self,
                                  char *message,
                                  Sudoku_t *sudoku) {
  uint8_t row = message[1] - '0';
  uint8_t column = message[2] - '0';
  uint8_t value = message[3] - '0';
  const char *messagePut = sudokuPut(sudoku,
                                     (int) value,
                                     (int) row,
                                     (int) column);
  if (strcmp(messagePut, "OK\n") == 0) {
    getBoardView(self, sudoku);
  } else {
    getSudokuMessage(self, messagePut);
  }
}

/*
 * Funcion que setea el tamanio del response, luego setea el mensaje que debe enviarse desde el sudoku
 */
static void setParameters(Response_t *self, char *message, Sudoku_t *sudoku) {
  if (message[0] == 'G') {
    getBoardView(self, sudoku);
  }
  if (message[0] == 'P') {
    evaluatePutParameters(self, message, sudoku);
  }
  if (message[0] == 'V') {
    const char *messageVerify = sudokuVerify(sudoku);
    getSudokuMessage(self, messageVerify);
  }
  if (message[0] == 'R') {
    sudokuReset(sudoku);
    getBoardView(self, sudoku);
  }
}

/*
 * Crea un response para mandar hacia el cliente, el cual contiene:
 *  - Tamanio del mensaje en un char de 5 bytes
 *  - Mensaje en un char del tamanio especificado por el campo size_int
 */
void responseCreate(Response_t *self, char *message, Sudoku_t *sudoku) {
  self->size = (char *) malloc(sizeof(char) * 4);
  setParameters(self, message, sudoku);
}

/*
 * Libera los recursos usados por el response
 */
void responseDestroy(Response_t *self) {
  free(self->size);
  free(self->message);
}



