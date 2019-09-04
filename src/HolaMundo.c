#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "SudokuView.h"
#include "Sector.h"
#include "List.h"
#include "Socket.h"
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
  /*Board_t board;
  board_create(&board, "board.txt");
  printBoard(&board);
  int row;
  int column;
  printf("Introduzca fila sector: ");
  scanf("%i",&row);
  printf("Introduzca columna sector: ");
  scanf("%i",&column);
  Sector_t sector;
  sector_create(&sector,&board,row,column);
  print_sector(&sector);
  List_t list;
  list_create(&list);
  list_add(&list, 1);
  list_add(&list, 2);
  size_t size = list_size(&list);
  printf("%ld", size);
  list_destroy(&list);*/
  Socket_t socket;
  socket_create(&socket);
  socket_connect(&socket,"localhost","7777");
  socket_destroy(&socket);
  return 0;
}