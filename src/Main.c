#include <string.h>
#include <stdio.h>
#include "SudokuServer.h"
#include "SudokuClient.h"

static int __checkArguments(int argc, char **argv) {
  if (argc < 2) {
    printf("ERROR: Argumentos insuficientes\n");
    return 1;
  }
  if (strncmp(argv[1], "server", 6) == 0) {
    if (argc != 3) {
      printf("ERROR: Argumentos para server invalidos\n");
      return 1;
    }
  }
  if (strncmp(argv[1], "client", 6) == 0) {
    if (argc != 4) {
      printf("ERROR: Argumentos para cliente invalidos\n");
      return 1;
    }
  }
  return 0;
}
/*
 * Ciclo de vida del server.
 */
static int serverLoop(const char *port) {
  SudokuServer_t sudoku_server;
  if (sudokuServerStart(&sudoku_server, port) != 0) {
    return 1;
  }
  int res = 0;
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
  if (__checkArguments(argc, argv) != 0) {
    return 1;
  }
  if (strncmp(argv[1], "server", 6) == 0) {
    const char *port = argv[2];
    if (serverLoop(port) == 1) {
      return 1;
    }

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
