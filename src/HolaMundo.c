#include <string.h>
#include <stdio.h>
#include "Sudoku.h"
#include "SudokuView.h"

int main(int argc, char *argv[]) {
  /*char buffer[1024];
  char mode[20];
  int res = 0;
  Socket_t socket;
  socket_create(&socket);
  memcpy(mode, argv[1], strlen(argv[1]) + 1);
  if (strcmp(mode, "server") == 0) {
    const char *port = argv[2];
    if (socket_bind(&socket, port) == 1) {
      printf("Uso: ./tp server %s\n", port);
      res = 1;
    } else {
      res = socket_listen(&socket, 20);
      Socket_t accept_socket;
      res = socket_accept(&socket, &accept_socket);
      res = socket_receive(&accept_socket, buffer);
      res = socket_send(&accept_socket, "hola soy el server\ncomo te va\n?");
      socket_destroy(&accept_socket);
    }
  } else {
    if (strcmp(mode, "client") == 0) {
      const char *host = argv[2];
      const char *port = argv[3];
      if (socket_connect(&socket, host, port) == 1) {
        printf("Uso: ./tp client %s %s\n", host, port);
        res = 1;
      } else {
        res = socket_send(&socket, "hola soy el cliente");
        res = socket_receive(&socket, buffer);
      }
    } else {
      printf("Modo no soportado, el primer parámetro debe ser server o client\n");
      res = 1;
    }
  }
  socket_destroy(&socket);
  return res;*/
  Sudoku_t sudoku;
  sudokuStart(&sudoku);
  char view[722] = {' '};
  sudokuGet(&sudoku,view);
  printf("%s",(const char *) view);
  while (1) {
    char funcion;
    printf("Ingresa la funcion: ");
    scanf(" %c", &funcion);
    if (funcion == 'p') {
      uint8_t valor, fila, columna;
      printf("Ingresa valor,fila y columna: ");
      scanf(" %c%c%c", &valor, &fila, &columna);
      const char *res = sudokuPut(&sudoku, valor - '0', fila -'0', columna-'0');
      printf("%s\n",res);
    }
    if (funcion == 'v') {
      printf("%s\n",sudokuVerify(&sudoku));
    }
    if (funcion == 'g') {
      sudokuGet(&sudoku,view);
      printf("%s",(const char *) view);
    }
    if (funcion == 'r') {
      sudokuReset(&sudoku);
      sudokuGet(&sudoku,view);
      printf("%s",(const char *) view);
    }
    if (funcion == 'x') {
      break;
    }
  }
  sudokuExit(&sudoku);
}

