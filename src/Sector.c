
#include "Sector.h"
#include <stdio.h>

void sector_create(Sector_t *self, Board_t *board, uint8_t sectorRow, uint8_t columnRow) {
  int row = sectorRow;
  int column = columnRow;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      self->cells[i][j].value = board->cells[i + (row * 3)][j + (column * 3)].value;
    }
  }
}

int sector_check_values(Sector_t *self) {
  return 0;
}
void sector_destroy(Sector_t *self) {

}

void print_sector(Sector_t *self) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%i", self->cells[i][j].value);
    }
    printf("\n");
  }
}
