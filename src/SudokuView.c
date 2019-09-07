#include "SudokuView.h"
#include "stdio.h"

void printBoard(Board_t *board) {
  /*char view[18][38];

  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 38; j++) {
      if (j % 12 == 0) {
        view[i][j] = 'U';
      } else {
        if (i % 6 == 0) {
          view[i][j] = '=';
        }
      }
    }
  }*/
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      Cell_t cell = board->cells[i][j];
      printf("%i", cell.value);
    }
    printf("\n");
  }
}
