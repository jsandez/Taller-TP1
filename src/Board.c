#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Board.h"

static int checkRow(const char *linea) {
  if (linea[17] != '\n') {
    printf("%c\n", linea[17]);
    printf("WRONG SIZE OF ROW");
    exit(2);
  }
  for (int i = 0; i < 9; i += 2) {
    if (!isdigit(linea[i])) {
      printf("NOT ALL DIGITS ERROR");
      exit(3);
    }
  }
  return 0;
}

static int checkFormatFile(FILE *f_source) {
  char linea[19];
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
  FILE *fsource = fopen(filepath, "r");
  char ch;
  checkFile(fsource);
  rewind(fsource);
  int row = 0, column = 0;
  while ((ch = fgetc(fsource)) != EOF) {
    if (ch == '\n') {
      row++;
      column = 0;
    } else {
      if (ch != ' ') {
        int value = ch - '0';
        Cell_t cell = {value, value != 0};
        self->cells[row][column] = cell;
        column++;
      }
    }
  }
  *(self->board_copy) = *(self);
  fclose(fsource);
}

int boardPut(Board_t *self, uint8_t value, uint8_t row, uint8_t column) {
  if (self->cells[row - 1][column - 1].preFixed) {
    return -1;
  }
  self->cells[row - 1][column - 1].value = value;
  return 0;
}

void boardReset(Board_t *self) {
  *self = *(self->board_copy);
}

void boardDestroy(Board_t *self) {
  free(self->board_copy);
}
