#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>
#include <stdint.h>

/*
 * TDA que representa el tablero del sudoku.
 * Contiene un vector de celdas de 9x9 y
 * cada celda tiene un valor y un flag
 * que representa si es un valor modificable
 * o no.
 */
typedef struct {
  uint8_t value;
  bool preFixed;
} Cell_t;

typedef struct Board {
  Cell_t cells[9][9];
}Board_t;

/*
 * Recibe un puntero al tda y un nombre de archivo.
 * Crea el tablero con los datos que lee del archivo.
 */
void boardCreate(Board_t *self, const char *filepath);

/*
 * Inserta un valor en el tablero.
 * No verifica valores, la responsabilidad de verificar
 * tanto valores como indices esta del lado del cliente
 * o del sudoku.
 */
int boardPut(Board_t *self, uint8_t value, uint8_t row, uint8_t column);

/*
 * Obtiene una vista del estado del tablero.
 */
void boardGet(Board_t *self,char *view);

/*
 * Resetea los valores a los que se habian
 * cargado en el inicio del programa.
 */
void boardReset(Board_t *self);

/*
 * Libera recursos.
 */
void boardDestroy(Board_t *self);

#endif

