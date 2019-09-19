#include <string.h>
#include <stdio.h>
#include "SudokuServer.h"
#include "SudokuClient.h"

/*
 * Ciclo de vida del server.
 */
static int serverLoop(const char *port) {
  SudokuServer_t sudoku_server;
  int res = sudokuServerStart(&sudoku_server, port);
  while (res == 0) {
    res = sudokuServerAlive(&sudoku_server);
  }
  sudokuServerStop(&sudoku_server);
  return res;
}

/*
 * Ciclo de vida del cliente.
 */
static int clientLoop(const char *host, const char *port) {
  SudokuClient_t sudoku_client;
  int res = sudokuClientStart(&sudoku_client, host, port);
  while (!res) {
    res = sudokuClientPlay(&sudoku_client);
  }
  sudokuClientStop(&sudoku_client);
  return res;
}

/*
 * Funcion principal que realiza los
 * ciclos de vida, dependiendo si es
 * servidor o cliente.
 */
int main(int argc, char *argv[]) {
  int res = 0;
  if (argc == 1) {
    printf("ERROR: No hay argumentos\n");
    return 1;
  }
  if (strncmp(argv[1], "server", 6) == 0) {
    const char *port = argv[2];
    res = serverLoop(port);
  } else {
    if (strncmp(argv[1], "client", 6) == 0) {
      res = clientLoop(argv[2], argv[3]);
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
