#include <stdlib.h>
#include "Board.h"
#include "SudokuFileManager.h"

void board_create(Board_t *self, const char *filepath) {
  Board_t *board_copy = (Board_t *) malloc(sizeof(Board_t));
  loadBoardFromFile(board_copy,filepath);
  self->board_copy = board_copy;
  loadBoardFromFile(self, filepath);
}

void board_put(Board_t *self, const int row, const int column, int value) {
  // CHEQUEAR VALORES DE ROW Y COLUMN
  if (self->cells[row - 1][column - 1].preFixed) {
    // AVISAR QUE NO SE PUEDE CAMBIAR
  }
  self->cells[row - 1][column - 1].value = value;
}

int board_get(Board_t *self, const int row, const int column) {
  return self->cells[row - 1][column - 1].value;
}

void board_destroy(Board_t *self) {
  free(self->board_copy);
}

