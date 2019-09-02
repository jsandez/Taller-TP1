#ifndef _SECTOR_H_
#define _SECTOR_H_
#include "Board.h"

typedef struct {
  cell_t cells[3][3];
} sector_t;

void sector_create(sector_t *self, board_t *board,const int sectorRow, const int columnRow);
int sector_check_values(sector_t *self);
void sector_destroy(sector_t *self);
void print_sector(sector_t* self);

#endif
