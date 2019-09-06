#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include "Board.h"

void sudokuPut(Board_t *board, int row, int column, int value);
const char *sudokuVerify(Board_t *board);
void sudokuReset(Board_t *board);
void sudokuGet(Board_t *board);
void sudokuExit(Board_t *board);

#endif
