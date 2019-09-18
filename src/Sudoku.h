#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include "Board.h"

typedef struct {
  Board_t board;
} Sudoku_t;

void sudokuStart(Sudoku_t *self);
const char *sudokuPut(Sudoku_t *self,
                      uint8_t value,
                      uint8_t row,
                      uint8_t column);
const char *sudokuVerify(Sudoku_t *self);
void sudokuReset(Sudoku_t *self);
void sudokuGet(Sudoku_t *self, char view[722]);
void sudokuExit(Sudoku_t *self);

#endif
