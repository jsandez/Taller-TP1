#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <netinet/in.h>
#include "SudokuClient.h"
#include "Socket.h"
#include "Commands.h"

static int getInput(char command[5]) {
  printf("Ingresar comando: \n");
  char message[20] = {0}, c, i = 0;
  while ((c = fgetc(stdin)) != '\n') {
    message[i] = c;
    i++;
  }
  message[i] = '\0';
  return decode(message, command);
}

int sudokuClientStart(SudokuClient_t *self, const char *host, const char *port) {
  int res = 0;
  self->socket = (Socket_t*)malloc(sizeof(Socket_t));
  socketCreate(self->socket);
  if (socketConnect(self->socket, host, port) == 1) {
    printf("Uso: ./tp client %s %s\n", host, port);
    res = 1;
  } /*else {
    char command[5] = {0};
    getInput(command);
    res = socketSend(self->socket, command, 1024);
    char buffer_msg_size[4];
    socketReceive(self->socket, buffer_msg_size, 4);
    uint32_t size_of_message = 0;
    char size[4];
    for (int i = 0; i < 4; i++) {
      size[i] = buffer_msg_size[i];
    }
    memcpy(&size_of_message, buffer_msg_size, sizeof(uint32_t));
    uint32_t msg_size = ntohl(size_of_message);
    char buffer_msg[msg_size + 1];
    res = socketReceive(self->socket, buffer_msg, msg_size + 1);
    printf("%s", buffer_msg);
  }*/
  return res;
}

int sudokuClientPlay(SudokuClient_t *self){
  int res = 0;
  char command[5] = {0};
  res = getInput(command);
  if (res == 1) {
    socketDestroy(self->socket);
    return 1;
  }
  res = socketSend(self->socket, command, 5);
  char buffer_msg_size[4];
  socketReceive(self->socket, buffer_msg_size, 4);
  uint32_t size_of_message = 0;
  char size[4];
  for (int i = 0; i < 4; i++) {
    size[i] = buffer_msg_size[i];
  }
  memcpy(&size_of_message, buffer_msg_size, sizeof(uint32_t));
  uint32_t msg_size = ntohl(size_of_message);
  char buffer_msg[msg_size];
  res = socketReceive(self->socket, buffer_msg, msg_size);
  printf("%s", buffer_msg);
  return res;
}
void sudokuClientStop(SudokuClient_t *self) {
  socketDestroy(self->socket);
  free(self->socket);
}