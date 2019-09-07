#include "SudokuView.h"
#include "stdio.h"

void getBoardView(Board_t *board, char view[722]) {
  char matrixView[19][38] = {' '};
  for (int i = 0; i < 19; i++) { // AGREGO FIN DE LINEA
    matrixView[i][37] = '\n';
  }
  int j = 0; // AGREGO SEPARADORES DE A 12 COLUMNAS
  while (j < 37) {
    for (int i = 0; i < 19; i++) {
      matrixView[i][j] = 'U';
    }
    j += 12;
  }
  int i = 0; //AGREGO SEPARADORES DE A  6 FILAS
  while (i < 19) {
    for (int j = 0; j < 36; j++) {
      if ((j + 12) % 12 != 0) {
        matrixView[i][j] = '=';
      }
    }
    i += 6;
  }
  // AGREGO LOS VALORES DE SUDOKU
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
  j = 0;
  while (j < 37) { // AGREGO LOS SEPARADORES DE PIPE Y SIMBOLO MAS CADA 4 COLUMNAS
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
  i = 0; //AGREGO SEPARADORES DE A  2 FILAS
  while (i < 19) {
    for (int j = 0; j < 36; j++) {
      char c = matrixView[i][j];
      if (c == '\000') {
        matrixView[i][j] = '-';
      }
    }
    i += 2;
  }
  // AGREGO ESPACIOS CORRESPONDIES
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 38; j++) {
      char c = matrixView[i][j];
      if (c == '\000') {
        matrixView[i][j] = ' ';
      }
    }
  }

//REVISAR ULTIMO CARACTER
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
};