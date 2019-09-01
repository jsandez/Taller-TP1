#include "SudokuFileManager.h"
#include "SudokuGame.h"
#include <stdlib.h>
#include <stdio.h>

void readFile(const char *fileName) {
  FILE *fsource;
  char linea[9];
  fsource = fopen("board.txt", "r");
  if (fsource == NULL) {
    printf("ERROR");
    exit(1);
  }
  while (fgets(linea, sizeof(linea) + 1, fsource) != NULL) {
    printf("%s", linea);
  }
  fclose(fsource);
}
