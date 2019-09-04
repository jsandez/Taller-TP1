#ifndef _SUDOKUFILE_MANAGER_H_
#define _SUDOKUFILE_MANAGER_H_
#include "Board.h"
#include <stdio.h>

void loadBoardFromFile(Board_t *board, const char *fName);
int checkRow(const char *linea);
int checkFormatFile(FILE *fsource);
void checkFile(FILE *fsource);

#endif
