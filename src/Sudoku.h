#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include "Board.h"

typedef struct {
  Board_t *board;
} Sudoku_t;

void sudokuStart(Sudoku_t *self);
void sudokuPut(Sudoku_t *self, int row, int column, int value);
const char *sudokuVerify(Sudoku_t *self);
void sudokuReset(Sudoku_t *self);
void sudokuGet(Sudoku_t *self, int row, int column);
void sudokuExit(Sudoku_t *self);

#endif
