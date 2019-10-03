#include "Sudoku.h"
#include "Sector.h"

/*
 * Chequea numeros duplicados en un array de 9 enteros.
 * Omite el 0.
 */
static int __checkDuplicatesInArray(int *array) {
  for (int i = 0; i < 8; i++) {
    for (int j = i + 1; j < 9; j++) {
      if ((array[i] == array[j]) && (array[i] != 0)) {
        return -1;
      }
    }
  }
  return 0;
}

/*
* Chequea duplicados en un sector correspondiente.
 */
static int __checkDuplicatesInSector(Sector_t *sector) {
  int array[9];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      int index = i * 3 + j;
      array[index] = sector->cells[i][j].value;
    }
  }
  return __checkDuplicatesInArray(array);
}

/*
 * Chequea repetidos en todos los sectores.
 */
static int __checkAllSectors(Board_t *board) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      Sector_t sector;
      sector_create(&sector, board, i, j);
      if (__checkDuplicatesInSector(&sector) == -1)
        return -1;
    }
  }
  return 0;
}

/*
 * Chequea repetidos en todas las columnas.
 */
static int __checkAllColumns(Board_t *board) {
  for (int i = 0; i < 9; i++) {
    int array[9];
    for (int j = 0; j < 9; j++) {
      array[j] = board->cells[i][j].value;
    }
    if (__checkDuplicatesInArray(array) == -1)
      return -1;
  }
  return 0;
}

/*
 * Chequea repetidos en todas las filas.
 */
static int __checkAllRows(Board_t *board) {
  for (int j = 0; j < 9; j++) {
    int array[9];
    for (int i = 0; i < 9; i++) {
      array[i] = board->cells[i][j].value;
    }
    if (__checkDuplicatesInArray(array) == -1)
      return -1;
  }
  return 0;
}

int sudokuStart(Sudoku_t *self) {
  return boardCreate(&self->board, "board.txt");
}

const char *sudokuPut(Sudoku_t *self,
                      uint8_t value,
                      uint8_t row,
                      uint8_t column) {
  if (boardPut(&self->board, value, row, column) == -1) {
    return "La celda indicada no es modificable\n";
  }
  return "OK\n";
}

const char *sudokuVerify(Sudoku_t *self) {
  if (__checkAllSectors(&self->board) == 0) {
    if (__checkAllRows(&self->board) == 0) {
      if (__checkAllColumns(&self->board) == 0) {
        return "OK\n";
      }
    }
  }
  return "ERROR\n";
}

void sudokuReset(Sudoku_t *self) {
  boardReset(&self->board);
}

void sudokuGet(Sudoku_t *self, char **view) {
  boardGet(&self->board, view);
}

void sudokuExit(Sudoku_t *self) {
  boardDestroy(&self->board);
}
