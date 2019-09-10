#ifndef _RESPONSE_H_
#define _RESPONSE_H_
#include <stdint.h>
#include "Sudoku.h"

typedef struct {
  uint32_t size_int;
  char *size;
  char *message;
} Response_t;

void responseCreate(Response_t *self, char *message, Sudoku_t *sudoku);
void responseDestroy(Response_t *self);

#endif
