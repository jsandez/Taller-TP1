#include <stdio.h>
#include "SudokuClient.h"
#include "Socket.h"
#include "Commands.h"

int startClient(const char *host, const char *port) {
  int res = 0;
  Socket_t socket;
  socketCreate(&socket);
  char bufferRecv[1024];
  if (socketConnect(&socket, host, port) == 1) {
    printf("Uso: ./tp client %s %s\n", host, port);
    res = 1;
  } else {
    char message[1024] = {0}, command[1024] = {0}, c, i = 0;
    printf("Escribi un mensaje: \n");
    while ((c = fgetc(stdin)) != '\n') {
      message[i] = c;
      i++;
    }
    message[i] = '\0';
    decode(message, command);
    res = socketSend(&socket, command, 1024);
    char buffer_msg_size[1024];
    socketReceive(&socket, bufferRecv, 1024);
    /*uint32_t size_of_message = 0;
    char size[4];
    for (int i = 0; i < 4; i++) {
      buffer_msg_size[i] = size[i];
    }
    memcpy(&size_of_message, buffer_msg_size, sizeof(uint32_t));
    uint32_t msg_size = ntohl(size_of_message);
    char buffer_msg[msg_size + 1];
    res = socketReceive(&socket, buffer_msg, strlen(buffer_msg));*/
    printf("%s", bufferRecv);
    socketDestroy(&socket);
  }
}