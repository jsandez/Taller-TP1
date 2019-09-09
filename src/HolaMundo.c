#include <string.h>
#include <stdio.h>
#include <netinet/in.h>
#include "Sudoku.h"
#include "SudokuView.h"
#include "Socket.h"
#include "Commands.h"
#include "Response.h"
#include "SudokuServer.h"
#include "SudokuClient.h"

int main(int argc, char *argv[]) {
  char mode[20];
  int res = 0;
  memcpy(mode, argv[1], strlen(argv[1]) + 1);
  if (strcmp(mode, "server") == 0) {
    SudokuServer_t *sudoku_server = malloc(sizeof(SudokuServer_t));
    const char *port = argv[2];
    res = sudokuServerStart(sudoku_server, port);
    while (!res) {
      res = sudokuServerAlive(sudoku_server);
    }
    sudokuServerStop(sudoku_server);
  } else {
    if (strcmp(mode, "client") == 0) {
      SudokuClient_t sudoku_client;
      const char *host = argv[2];
      const char *port = argv[3];
      res = sudokuClientStart(&sudoku_client, host, port);
      while (!res) {
        res = sudokuClientPlay(&sudoku_client);
      }
      sudokuClientStop(&sudoku_client);
    } else {
      printf("Modo no soportado, el primer parámetro debe ser server o client\n");
      res = 1;
    }
  }
  return res;
}