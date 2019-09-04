#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>

typedef struct Cell{
  int value;
  bool preFixed;
} Cell_t;

typedef struct Board {
  Cell_t cells[9][9];
} Board_t;

void board_create(Board_t *self, const char *filepath);
void board_put(Board_t *self, const int row, const int column, const int value);
int board_get(Board_t *self, const int row, const int column);
void board_destroy(Board_t *self);

#endif