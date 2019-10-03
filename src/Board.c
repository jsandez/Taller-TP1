#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Board.h"

/*
 * Template que sirve como plantilla
 * para el formato en que se va a presentar
 * el tablero al usuario.
 */
static char *__template_view = "U===========U===========U===========U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U---+---+---U---+---+---U---+---+---U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U---+---+---U---+---+---U---+---+---U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U===========U===========U===========U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U---+---+---U---+---+---U---+---+---U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U---+---+---U---+---+---U---+---+---U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U===========U===========U===========U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U---+---+---U---+---+---U---+---+---U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U---+---+---U---+---+---U---+---+---U\n"
                               "U X | X | X U X | X | X U X | X | X U\n"
                               "U===========U===========U===========U\n";

/*
 * Funcion auxiliar que chequea la cantidad
 * de filas que tienen las lineas del archivo
 * de entrada. Tambien chequea que TODOS los
 * caracteres sean solo digitos.
 */
static int __checkColumns(const char *linea) {
  if (linea[17] != '\n') {
    printf("%c\n", linea[17]);
    printf("WRONG SIZE OF COLUMN");
    return 1;
  }
  for (int i = 0; i < 9; i += 2) {
    if (!isdigit(linea[i])) {
      printf("NOT ALL DIGITS ERROR");
      return 1;
    }
  }
  return 0;
}

/*
 * Funcion auxiliar que chequea el tamanio de
 * filas que tiene el archivo de entrada. Llama a
 * la funcion que chequea las columnas por cada
 * fila.
 */
static int __checkRows(FILE *f_source) {
  char linea[19];
  int amount_of_rows = 0;
  while (fgets(linea, sizeof(linea), f_source) != NULL) {
    amount_of_rows++;
    if (__checkColumns(linea) != 0) {
      return 1;
    }
    if (amount_of_rows > 9) {
      printf("MORE THAN 9 ROWS");
      return 1;
    }
  }
  if (amount_of_rows < 9) {
    printf("LESS THAN 9 ROWS");
    return 1;
  }
  return 0;
}

/*
 * Funcion auxilizar que realiza los chequeos
 * correspondientes y tambien que el archivo
 * no sea NULL.
 */
static int __checkFile(FILE *f_source) {
  if (f_source == NULL) {
    printf("INPUT ERROR");
    return 1;
  }
  return __checkRows(f_source);
}

int boardCreate(Board_t *self, const char *filepath) {
  FILE *fsource = fopen(filepath, "r");
  char ch;
  if (__checkFile(fsource) != 0) {
    return 1;
  }
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
  fclose(fsource);
  return 0;
}

int boardPut(Board_t *self, uint8_t value, uint8_t row, uint8_t column) {
  if (self->cells[row - 1][column - 1].preFixed) {
    return -1;
  }
  self->cells[row - 1][column - 1].value = value;
  return 0;
}

void boardReset(Board_t *self) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (!(self->cells[i][j].preFixed)) {
        self->cells[i][j].value = 0;
      }
    }
  }
}

void boardGet(Board_t *self, char **view) {
  *view = (char *) malloc(722);
  memcpy(*view, __template_view, 722);
  char *pch;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      pch = strchr(*view, 'X');
      uint8_t value = self->cells[i][j].value;
      if (value == 0) {
        *pch = ' ';
      } else {
        *pch = (char) value + '0';
      }
    }
  }
}

void boardDestroy(Board_t *self) {}
