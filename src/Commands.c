#include <stdint-gcc.h>
#include "Commands.h"
#include "string.h"

static void getSubstring(const char *string, char *substring, int position, int length) {
  int c = 0;
  while (c < length) {
    substring[c] = string[position + c - 1];
    c++;
  }
  substring[c] = '\0';
}

static void evaluatePut(const char *stdIn, char *message) {
  char substring_1[5], substring_2[5], substring_3[2];
  getSubstring(stdIn, substring_1, 1, 4);
  getSubstring(stdIn, substring_2, 6, 4);
  getSubstring(stdIn, substring_3, 11, 1);
  if ((!strcmp(substring_1, "put ")) && (!strcmp(substring_2, " in ")) && (!strcmp(substring_3, ","))) {
    char value, row, column;
    getSubstring(stdIn, &value, 5, 1);
    getSubstring(stdIn, &row, 10, 1);
    getSubstring(stdIn, &column, 12, 1);
    message[0] = 'P';
    message[1] = (uint8_t) row;
    message[2] = (uint8_t) column;
    message[3] = (uint8_t) value;
  }
}

void decode(char *stdIn, char *message) {
  evaluatePut(stdIn, message);
  if (!strcmp(stdIn, "verify")) {
    message[0] = 'V';
  }
  if (!strcmp(stdIn, "reset")) {
    message[0] = 'R';
  }
  if (!strcmp(stdIn, "get")) {
    message[0] = 'G';
  }
  if (!strcmp(stdIn, "exit")) {
    message[0] = 'X';
  }
}
