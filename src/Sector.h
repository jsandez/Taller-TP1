#ifndef _SECTOR_H_
#define _SECTOR_H_
#include <stdint.h>
#include "Board.h"

typedef struct {
  Cell_t cells[3][3];
} Sector_t;

void sector_create(Sector_t *self,
                   Board_t *board,
                   uint8_t sectorRow,
                   uint8_t columnRow);

#endif
