#ifndef _SUDOKUCLIENT_H_
#define _SUDOKUCLIENT_H_
#include "Socket.h"

/*
 * TDA que representa al sudoku visto
 * del lado del cliente.
 */
typedef struct {
  Socket_t socket;
} SudokuClient_t;

/*
 * Inicia el cliente conectandose a un host y puerto especificado.
 * Return: 0 si se conecto bien
 *         1 si no pudo conectarse
 */
int sudokuClientStart(SudokuClient_t *self, const char *host, const char *port);

/*
 * Ciclo de vida de juego del sudoku, del lado del cliente
 * Retorna: 0 si se debe seguir jugando
 *          1 si se quiere cerrar el juego
 *          Lo que devuelva send
 *          Lo que devuelva recv
 */
int sudokuClientPlay(SudokuClient_t *self);

/*
 * Finaliza el juego del lado del cliente.s
 */
void sudokuClientStop(SudokuClient_t *self);

#endif
