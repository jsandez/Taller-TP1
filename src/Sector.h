#ifndef _SECTOR_H_
#define _SECTOR_H_
#include "Board.h"

typedef struct {
  Cell_t cells[3][3];
} Sector_t;

void sector_create(Sector_t *self, Board_t *board, const int sectorRow, const int columnRow);
int sector_check_values(Sector_t *self);
void sector_destroy(Sector_t *self);
void print_sector(Sector_t* self);

#endif
