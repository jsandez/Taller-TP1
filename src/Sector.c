
#include "Sector.h"
#include <stdio.h>

void sector_create(sector_t *self, board_t *board,const int sectorRow, const int columnRow) {
  int row = sectorRow - 1;
  int column = columnRow - 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      self->cells[i][j].value = board->cells[i+(row*3)][j+(column*3)].value;
    }
  }
}

int sector_check_values(sector_t *self) {
  return 0;
}
void sector_destroy(sector_t *self) {

}

void print_sector(sector_t* self) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%i",self->cells[i][j].value);
    }
    printf("\n");
  }
}
