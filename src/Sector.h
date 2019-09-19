#ifndef _SECTOR_H_
#define _SECTOR_H_
#include <stdint.h>
#include "Board.h"

/*
 * TDA que solo sirve para representar
 * un mini-tablero de 3x3 que luego sera
 * utilizado para chequear si contiene
 * valores repetidos.
 */
typedef struct {
  Cell_t cells[3][3];
} Sector_t;

void sector_create(Sector_t *self,
                   Board_t *board,
                   uint8_t sectorRow,
                   uint8_t columnRow);

#endif
