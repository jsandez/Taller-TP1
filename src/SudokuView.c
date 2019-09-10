#include "SudokuView.h"

static void addSpacesAndSeparators(char matrixView[19][38]) {
  int i = 0;
  while (i < 19) {
    for (int j = 0; j < 36; j++) {
      char c = matrixView[i][j];
      if (c == '\000') {
        matrixView[i][j] = '-';
      }
    }
    i += 2;
  }
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 38; j++) {
      char c = matrixView[i][j];
      if (c == '\000') {
        matrixView[i][j] = ' ';
      }
    }
  }
}

static void addPipesAndPlus(char matrixView[19][38]) {
  int j = 0;
  while (j < 37) {
    for (int i = 0; i < 19; i++) {
      char c = matrixView[i][j];
      if (c == '\000') {
        int i_1 = i + 1;
        if (i_1 % 2 == 0) {
          matrixView[i][j] = '|';
        } else {
          matrixView[i][j] = '+';
        }
      }
    }
    j += 4;
  }
}

static void addSudokuValues(Board_t *board, char matrixView[19][38]) {
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 36; j++) {
      int i_2 = i + 1;
      int j_2 = j + 2;
      if ((i_2 % 2 == 0)) {
        if ((j_2 % 4 == 0)) {
          Cell_t cell = board->cells[(i_2 / 2) - 1][(j_2 / 4) - 1];
          if (cell.value != 0) {
            matrixView[i][j] = (char) cell.value + '0';
          } else {
            matrixView[i][j] = ' ';
          }
        }
      }
    }
  }
}

static void addSeparators(char matrixView[19][38]) {
  int j = 0;
  while (j < 37) {
    for (int i = 0; i < 19; i++) {
      matrixView[i][j] = 'U';
    }
    j += 12;
  }
  int i = 0;
  while (i < 19) {
    for (int j = 0; j < 36; j++) {
      if ((j + 12) % 12 != 0) {
        matrixView[i][j] = '=';
      }
    }
    i += 6;
  }
}

void getBoardView(Board_t *board, char view[722]) {
  char matrixView[19][38] = {{' '},{' '}};
  for (int i = 0; i < 19; i++) {
    matrixView[i][37] = '\n';
  }
  addSeparators(matrixView);
  addSudokuValues(board, matrixView);
  addPipesAndPlus(matrixView);
  addSpacesAndSeparators(matrixView);
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 38; j++) {
      int index = i * 38 + j;
      char element = matrixView[i][j];
      if (element == ' ') {
        view[index] = ' ';
      } else {
        view[index] = matrixView[i][j];
      }
    }
  }
}
