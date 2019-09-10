#include <stdlib.h>
#include "Sudoku.h"
#include "SudokuView.h"
#include "Sector.h"

static int checkDuplicatesInArray(uint8_t array[]) {
  for (int i = 0; i < 8; i++) {
    for (int j = i + 1; j < 9; j++) {
      uint8_t aver = array[i];
      uint8_t aver2 = array[j];
      if ((array[i] == array[j]) && (array[i] != 0)) {
        return -1;
      }
    }
  }
  return 0;
}

static int checkDuplicatesInSector(Sector_t *sector) {
  uint8_t array[9];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      uint8_t index = i * 3 + j;
      array[index] = sector->cells[i][j].value;
    }
  }
  return checkDuplicatesInArray(array);
}

static int checkAllSectors(Board_t *board) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Sector_t sector;
      sector_create(&sector, board, i, j);
      if (checkDuplicatesInSector(&sector) == -1)
        return -1;
    }
  }
}

static int checkAllColumns(Board_t *board) {
  for (int i = 0; i < 9; i++) {
    uint8_t array[9];
    for (int j = 0; j < 9; j++) {
      array[j] = board->cells[i][j].value;
    }
    if (checkDuplicatesInArray(array) == -1)
      return -1;
  }
  return 0;
}

static int checkAllRows(Board_t *board) {
  for (int j = 0; j < 9; j++) {
    uint8_t array[9];
    for (int i = 0; i < 9; i++) {
      array[i] = board->cells[i][j].value;
    }
    if (checkDuplicatesInArray(array) == -1)
      return -1;
  }
  return 0;
}

/*
 * Constructor del sudoku con el archivo board.txt
 */
void sudokuStart(Sudoku_t *self) {
  Board_t *board = (Board_t *) malloc(sizeof(Board_t));
  boardCreate(board, "board.txt");
  self->board = board;
}

const char *sudokuPut(Sudoku_t *self, uint8_t value, uint8_t row, uint8_t column) {
  bool aver = (row > 9);
  if (row < 1 || row > 9 || column < 1 || column > 9) {
    return "Error en los índices. Rango soportado: [1,9]\n";
  }
  if (value < 1 || value > 9) {
    return "Error en el valor ingresado. Rango soportado: [1,9]\n";
  }
  if (boardPut(self->board, value, row, column) == -1) {
    return "La celda indicada no es modificable\n";
  }
  return "OK\n";
}

const char *sudokuVerify(Sudoku_t *self) {
  if (checkAllSectors(self->board) == 0) {
    if (checkAllRows(self->board) == 0) {
      if (checkAllColumns(self->board) == 0) {
        return "OK\n";
      }
    }
  }
  return "ERROR\n";
}

void sudokuReset(Sudoku_t *self) {
  boardReset(self->board);
}
void sudokuGet(Sudoku_t *self, char view[722]) {
  getBoardView(self->board, view);
}
void sudokuExit(Sudoku_t *self) {
  boardDestroy(self->board);
  free(self->board);
}
