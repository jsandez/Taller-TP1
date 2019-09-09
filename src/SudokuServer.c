#include <stdio.h>
#include "SudokuServer.h"
#include "Socket.h"

int startServer(const char *port) {
  int res= 0;
  Socket_t socket;
  socketCreate(&socket);
  char bufferRecv[1024];
  if (socketBind(&socket, port) == 1) {
    printf("Uso: ./tp server %s\n", port);
    res = 1;
  } else {
    res = socketListen(&socket, 20);
    Socket_t accept_socket;
    res = socketAccept(&socket, &accept_socket);
    res = socketReceive(&accept_socket, bufferRecv, 1024);
    //const char *asd = strcat("Mandaste esto ", bufferRecv);
    /*char bufferResponse[727] = {0};
    evaluateCommand(bufferRecv, bufferResponse);
    char buffer_size[4];
    for (int i = 0; i < 4; i++) {
      buffer_size[i] = bufferResponse[i];
    }
    char secondBuffer[723];
    for (int i = 0; i < 4; i++) {
      secondBuffer[i] = bufferResponse[i+4];
    }
    res = socketSend(&accept_socket, buffer_size, 4);*/
    res = socketSend(&accept_socket, bufferRecv, 1024);
    socketDestroy(&socket);
  }
}
