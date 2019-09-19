#ifndef _SUDOKU_H_
#define _SUDOKU_H_
#include "Board.h"

/*
 * TDA que representa el juego sudoku
 * y todas las operaciones correspondientes.
 * Tiene un board en su interior.
 */
typedef struct {
  Board_t board;
} Sudoku_t;

/*
 * Operacion que inicia el juego sudoku.
 * Crea el board correspondiente al archivo
 * board.txt.
 */
void sudokuStart(Sudoku_t *self);

/*
 * Ingresa un valor en el tablero, siempre y
 * cuando sea de una celda modificable.
 */
const char *sudokuPut(Sudoku_t *self,
                      uint8_t value,
                      uint8_t row,
                      uint8_t column);

/*
 * Verifica el estado del sudoku. Puede ser
 * OK o ERROR.
 */
const char *sudokuVerify(Sudoku_t *self);

/*
 * Resetea el tablero al estado del comienzo.
 */
void sudokuReset(Sudoku_t *self);

/*
 * Obtiene una representacion del sudoku la cual
 * la guarda en el string pasado por parametro.
 */
void sudokuGet(Sudoku_t *self, char view[722]);

/*
 * Libera los recursos del juego.
 * Destruye el tablero.
 */
void sudokuExit(Sudoku_t *self);

#endif
