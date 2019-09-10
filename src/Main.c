#include <string.h>
#include <stdio.h>
#include "SudokuView.h"
#include "SudokuServer.h"
#include "SudokuClient.h"

static int serverLoop(const char *port) {
  int res = 0;
  SudokuServer_t sudoku_server;
  res = sudokuServerStart(&sudoku_server, port);
  while (res == 0) {
    res = sudokuServerAlive(&sudoku_server);
  }
  sudokuServerStop(&sudoku_server);
  return res;
}

static int clientLoop(const char *host, const char *port) {
  int res = 0;
  SudokuClient_t sudoku_client;
  res = sudokuClientStart(&sudoku_client, host, port);
  while (!res) {
    res = sudokuClientPlay(&sudoku_client);
  }
  sudokuClientStop(&sudoku_client);
  return res;
}

int main(int argc, char *argv[]) {
  char mode[20];
  int res = 0;
  memcpy(mode, argv[1], strlen(argv[1]) + 1);
  if (strcmp(mode, "server") == 0) {
    const char *port = argv[2];
    res = serverLoop(port);
  } else {
    if (strcmp(mode, "client") == 0) {
      const char *host = argv[2];
      const char *port = argv[3];
      res = clientLoop(host, port);
    } else {
      printf("Modo no soportado, "
             "el primer parámetro debe ser server o client\n");
      return 1;
    }
  }
  if (res == 0 || res == 2) {
    return 0;
  }
}
