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
    const char *port = argv[2];
    res = startServer(port);
  } else {
    if (strcmp(mode, "client") == 0) {
      const char *host = argv[2];
      const char *port = argv[3];
      res = startClient(host, port);
    } else {
      printf("Modo no soportado, el primer parámetro debe ser server o client\n");
      res = 1;
    }
  }
  return res;
}