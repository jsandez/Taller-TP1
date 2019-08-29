#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct palabra {
  char palabra[20];
} palabra_t;

int main(int argc, char *argv[]) {
  FILE *fsource;
  palabra_t traductor;
  fsource = fopen("../hola.txt", "r");
  if (fsource == NULL) {
    printf("ERROR");
    exit(1);
  }
  while (!feof(fsource)) {
    if (fread((void *) &traductor, sizeof(traductor), 1, fsource)) {
      printf("%s", traductor.palabra);
    }
  }
  fclose(fsource);
  printf("termino");
  return 0;
}