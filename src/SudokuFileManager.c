#include "SudokuFileManager.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

void loadBoardFromFile(Board_t *board, const char *fName) {
  FILE *fsource;
  char linea[11];
  fsource = fopen(fName, "r");
  checkFile(fsource);
  rewind(fsource);
  while (fgets(linea, sizeof(linea), fsource) != NULL) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        int value = linea[j] - '0';
        Cell_t cell = {value, false};
        board->cells[i][j] = cell;
      }
    }
  }
  fclose(fsource);
}

int checkRow(const char *linea) {
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

int checkFormatFile(FILE *fsource) {
  char linea[11];
  int amountOfRows = 0;
  while (fgets(linea, sizeof(linea), fsource) != NULL) {
    amountOfRows++;
    checkRow(linea);
    if (amountOfRows > 9) {
      printf("MORE THAN 9 ROWS");
      exit(4);
    }
  }
  if (amountOfRows < 9) {
    printf("LESS THAN 9 ROWS");
    exit(5);
  }
  return 0;
}

void checkFile(FILE *fsource) {
  if (fsource == NULL) {
    printf("INPUT ERROR");
    exit(1);
  }
  checkFormatFile(fsource);
}