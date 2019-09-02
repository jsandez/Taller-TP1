#include "SudokuView.h"

void printBoard(board_t *board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cell_t cell = board->cells[i][j];
      printf("%i", cell.value);
    }
    printf("\n");
  }
}
