#ifndef _RESPONSE_H_
#define _RESPONSE_H_
#include <stdint.h>
#include "Sudoku.h"

/*
 * TDA que crea el response correspondiente
 * que el servidor debe enviar a el
 * cliente. Se comunica con la clase
 * Sudoku para obtener los valores
 * correspondientes.
 */
typedef struct {
  uint32_t size;
  char *message;
} Response_t;

/*
 * Crea un response dado un puntero
 * al TDA response, un comando que
 * determinara la operacion a realizar,
 * parametros (si fueran necesarios)
 * y un puntero a una variable de tipo
 * sudoku para realizar las operaciones correspondientes.
 */
void responseCreate(Response_t *self,
                    char command,
                    char *params,
                    Sudoku_t *sudoku);

/*
 * Libera recursos.
 */
void responseDestroy(Response_t *self);

#endif
