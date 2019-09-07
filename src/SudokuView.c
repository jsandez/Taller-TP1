#include "SudokuView.h"
#include "stdio.h"

void printBoard(Board_t *board) {
  char view[19][38] = {' '}; // INICIALIZO CON ESPACIO
  for (int i = 0; i < 19; i++) { // AGREGO FIN DE LINEA
    view[i][37] = '\n';
  }
  int j = 0; // AGREGO SEPARADORES DE A 12 COLUMNAS
  while (j < 37) {
    for (int i = 0; i < 19; i++) {
      view[i][j] = 'U';
    }
    j += 12;
  }
  int i = 0; //AGREGO SEPARADORES DE A  6 FILAS
  while (i < 19) {
    for (int j = 0; j < 36; j++) {
      if ((j + 12) % 12 != 0) {
        view[i][j] = '=';
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
            view[i][j] = (char) cell.value + '0';
          } else {
            view[i][j] = ' ';
          }
        }
      }
    }
  }
  j = 0;
  while (j < 37) { // AGREGO LOS SEPARADORES DE PIPE Y SIMBOLO MAS CADA 4 COLUMNAS
    for (int i = 0; i < 19; i++) {
      char c = view[i][j];
      if (c == '\000') {
        int i_1 = i + 1;
        if (i_1 % 2 == 0) {
          view[i][j] = '|';
        } else {
          view[i][j] = '+';
        }
      }
    }
    j += 4;
  }
  i = 0; //AGREGO SEPARADORES DE A  2 FILAS
  while (i < 19) {
    for (int j = 0; j < 36; j++) {
      char c = view[i][j];
      if (c == '\000') {
        view[i][j] = '-';
      }
    }
    i += 2;
  }
  // AGREGO ESPACIOS CORRESPONDIES
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 38; j++) {
      char c = view[i][j];
      if (c == '\000') {
        view[i][j] = ' ';
      }
    }
  }

//REVISAR ULTIMO CARACTER
  for (int i = 0; i < 19; i++) {
    for (int j = 0; j < 38; j++) {
      printf("%c", view[i][j]);
    }
  }
};