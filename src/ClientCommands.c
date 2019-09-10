#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "ClientCommands.h"

static int evaluatePut(const char *stdIn, char *message) {
  int row;
  int column;
  int value;
  int res = sscanf(stdIn, "put %i in %i,%i", &value, &row, &column);
  if (res != 3) {
    return 1;
  } else {
    if (row < 1 || column > 9 || column < 1 || column > 9) {
      fprintf(stderr, "Error en los índices. Rango soportado: [1,9]\n");
      return 2;
    }
    if (value < 1 || value > 9) {
      fprintf(stderr, "Error en el valor ingresado. Rango soportado: [1,9]\n");
      return 2;
    }
    message[0] = 'P';
    message[1] = row+'0';
    message[2] = column+'0';
    message[3] = value+'0';
    return 0;
  }
}

/*
 * Comandos que se van a leer desde stdIn. Si es incorrecto, vuelve a preguntar hasta que se ingrese
 * uno correcto.
 * Devuelve: 0 si el comando es correcto
 *           1 si quiere salir del juego
 *           2 si es incorrecto
 */
int decode(char *stdIn, char *message) {
  int resultPut = 0;
  resultPut = evaluatePut(stdIn, message);
  if (resultPut != 1) {
    return resultPut;
  }
  if (!strcmp(stdIn, "verify")) {
    message[0] = 'V';
    return 0;
  }
  if (!strcmp(stdIn, "reset")) {
    message[0] = 'R';
    return 0;
  }
  if (!strcmp(stdIn, "get")) {
    message[0] = 'G';
    return 0;
  }
  if (!strcmp(stdIn, "exit")) {
    message[0] = 'X';
    return 1;
  }
  return 2;
}
