#ifndef _SUDOKUSERVER_H_
#define _SUDOKUSERVER_H_
#include "Socket.h"

typedef struct {
  Socket_t *socket;
  Socket_t *accept_socket;
} SudokuServer_t;

int sudokuServerStart(SudokuServer_t *self, const char *port);
int sudokuServerAlive(SudokuServer_t *self);
void sudokuServerStop(SudokuServer_t * self);

#endif
