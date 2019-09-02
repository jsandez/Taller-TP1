#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>

typedef struct {
  int value;
  bool preFixed;
} cell_t;

typedef struct {
  cell_t cells[9][9];
} board_t;

void board_create(board_t *self, const char *filepath);
void board_put(board_t *self, const int row, const int column, const int value);
int board_get(board_t *self, const int row, const int column);
void board_destroy(board_t *self);

#endif