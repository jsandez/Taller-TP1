#ifndef _SUDOKUSERVER_H_
#define _SUDOKUSERVER_H_
#include "Socket.h"
#include "Sudoku.h"

/*
 * TDA que representa el juego del
 * sudoku, visto desde el lado del servidor.
 */
typedef struct {
  Socket_t socket;
  Socket_t accept_socket;
  Sudoku_t sudoku;
} SudokuServer_t;

/*
 * Inicia el servidor en un puerto especificado
 * Devuelve:0 si se inicio correctamente
 *          1 si el puerto es incorrect, si hay error en el listen o en el accept
 */
int sudokuServerStart(SudokuServer_t *self, const char *port);

/*
 * Ciclo de vida del sudoku del lado del servidor
 * Devuelve: 0 si se tiene que seguir ejecutando
 *           1 si hubo algun error
 *           2 si se cerro el servidor del lado del cliente
 */
int sudokuServerAlive(SudokuServer_t *self);

/*
 * Libera los recursos del servidor
 */
void sudokuServerStop(SudokuServer_t *self);

#endif
