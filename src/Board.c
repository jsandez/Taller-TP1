#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Board.h"

static int checkRow(const char *linea) {
  if (linea[9] != '\n') {
    printf("WRONG SIZE OF ROW");
    exit(2);
  }
  for (int i = 0; i < 9; i++) {
    if (!isdigit(linea[i])) {
      printf("NOT ALL DIGITS ERROR");
      exit(3);
    }
  }
  return 0;
}

static int checkFormatFile(FILE *f_source) {
  char linea[11];
  int amount_of_rows = 0;
  while (fgets(linea, sizeof(linea), f_source) != NULL) {
    amount_of_rows++;
    checkRow(linea);
    if (amount_of_rows > 9) {
      printf("MORE THAN 9 ROWS");
      exit(4);
    }
  }
  if (amount_of_rows < 9) {
    printf("LESS THAN 9 ROWS");
    exit(5);
  }
  return 0;
}
static void checkFile(FILE *f_source) {
  if (f_source == NULL) {
    printf("INPUT ERROR");
    exit(1);
  }
  checkFormatFile(f_source);
}

void boardCreate(Board_t *self, const char *filepath) {
  self->board_copy = (Board_t *) malloc(sizeof(Board_t));
  FILE *fsource;
  char linea[11];
  fsource = fopen(filepath, "r");
  checkFile(fsource);
  rewind(fsource);
  while (fgets(linea, sizeof(linea), fsource) != NULL) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        int value = linea[j] - '0';
        Cell_t cell = {value, false};
        self->cells[i][j] = cell;
      }
    }
  }
  *(self->board_copy) = *(self);
  fclose(fsource);
}

int boardPut(Board_t *self, const int row, const int column, const int value) {
  if (self->cells[row - 1][column - 1].preFixed) {
    printf("Esta prefijado");
    return -1;
  }
  self->cells[row - 1][column - 1].value = value;
  return 0;
}

int boardGet(Board_t *self, const int row, const int column) {
  return self->cells[row - 1][column - 1].value;
}

void boardReset(Board_t *self) {
  *self = *(self->board_copy);
}
void boardDestroy(Board_t *self) {
  free(self->board_copy);
}
