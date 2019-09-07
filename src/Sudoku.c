#include <stdlib.h>
#include "Sudoku.h"

void sudokuStart(Sudoku_t *self) {
  Board_t *board = (Board_t*) malloc (sizeof(Board_t));
  boardCreate(board,"board.txt");
  self->board = board;
}

void sudokuPut(Sudoku_t *self, int row, int column, int value) {
  boardPut(self->board,row,column,value);
}
const char *sudokuVerify(Sudoku_t *self) {
  return "OK";
}
void sudokuReset(Sudoku_t *self) {
  boardReset(self->board);
}
void sudokuGet(Sudoku_t *self, int row, int column) {
  boardGet(self->board,row,column);
}
void sudokuExit(Sudoku_t *self){
  boardDestroy(self->board);
}
