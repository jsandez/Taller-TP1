#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "SudokuView.h"

int main(int argc, char *argv[]) {
  board_t board;
  board_load(&board, "board.txt");
  printBoard(&board);
  int value;
  int row;
  int column;
  printf("Introduce un valor: ");
  scanf("%i", &value);
  printf("Introduce fila: ");
  scanf("%i", &row);
  printf("Introduce columna2: ");
  scanf("%i", &column);
  board_put(&board, row, column, value);
  int valueGet = board_get(&board, 4, 4);
  printf("\nEl valor es: %i", valueGet);
  printf("reseteo");
  board_load(&board, "board.txt");
  printBoard(&board);
  return 0;
}