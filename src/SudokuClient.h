#ifndef _SUDOKUCLIENT_H_
#define _SUDOKUCLIENT_H_
#include "Socket.h"

typedef struct {
  Socket_t socket;
} SudokuClient_t;

int sudokuClientStart(SudokuClient_t *self, const char *host, const char *port);
int sudokuClientPlay(SudokuClient_t *self);
void sudokuClientStop(SudokuClient_t *self);

#endif
