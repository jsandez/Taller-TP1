#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>

typedef struct {
  int value;
  bool preFixed;
} Cell_t;

struct Board;
typedef struct Board Board_t;
struct Board {
  Cell_t cells[9][9];
  Board_t *board_copy;
};

void boardCreate(Board_t *self, const char *filepath);
int boardPut(Board_t *self, const int row, const int column, const int value);
int boardGet(Board_t *self, const int row, const int column);
void boardReset(Board_t *self);
void boardDestroy(Board_t *self);

#endif

