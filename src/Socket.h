#ifndef _SOCKET_H_
#define _SOCKET_H_
#include <stdlib.h>

/*
 * TDA que representa un socket
 * correspondiente con todas sus operaciones
 * posibles.
 */
typedef struct {
  int fd;
} Socket_t;

/*
 * Es la creacion de un socket
 * pero en este caso solo lo configura como invalido
 * en -1, hasta que haga el listen o el connect
 * correspondiente.
 */
void socketCreate(Socket_t *self);

/*
 * Se conecta a un socket, dado
 * un host y un servicio (o puerto)
 */
int socketConnect(Socket_t *self, const char *host, const char *service);

/*
 * Realiza el bind correspondiente en determinado
 * servicio (o puerto)
 */
int socketBind(Socket_t *self, const char *service);

/*
 * Configura hasta cuandos clientes tendra en espera.
 */
int socketListen(Socket_t *self, int waiting_clients);

/*
 * Cuando ingresa una conexion, la acepta.
 * Esta funcion es bloqueante hasta que se realice la conexion
 * correspondiente.
 */
int socketAccept(Socket_t *self, Socket_t *accept_socket);

/*
 * Envia un mensaje a traves del socket.
 */
int socketSend(Socket_t *self, const char *buf, int length);

/*
 * Recibe un mensaje a traves del socket.
 */
int socketReceive(Socket_t *self, char *buf, int length);

/*
 * Libera los recursos.
 */
void socketDestroy(Socket_t *self);

#endif

