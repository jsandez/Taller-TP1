#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>

typedef struct {
  int row;
  int column;
} coordinates_t;

typedef struct {
  coordinates_t coordinates;
  bool preFixed;
} cell_t;

typedef struct {
  cell_t cell[9][9];
  cell_t *iterator;
} board_t;

cell_t *get(const board_t *board, int row, int column);
int put(board_t *board, int row, int column, int value);

#endif