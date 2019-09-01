#include <stdio.h>
#include "Board.h"

cell_t *get(const board_t *board, int row, int column) {
  return board->iterator;
}
int put(board_t *board, int row, int column, int value) {
  return 0;
}

void printBoard(const board_t* board) {
  long num = 1111111111111111111;
  printf("%ld\n%ld",num,num);
}
