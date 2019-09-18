#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint8_t value;
  bool preFixed;
} Cell_t;

typedef struct Board {
  Cell_t cells[9][9];
}Board_t;

void boardCreate(Board_t *self, const char *filepath);
int boardPut(Board_t *self, uint8_t value, uint8_t row, uint8_t column);
void boardReset(Board_t *self);
void boardDestroy(Board_t *self);

#endif

