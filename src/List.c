#include <stdlib.h>
#include "List.h"

void list_create(List_t *self) {
  self->head = NULL;
}
void list_add(List_t *self, int data) {
  Node_t *current = self->head;
  Node_t *newNode = (Node_t *) malloc(sizeof(Node_t));
  newNode->data = data;
  newNode->next = NULL;
  if (current == NULL) {
    self->head = newNode;
  } else {
    while (current->next) {
      current = current->next;
    }
    current->next = newNode;
  }
}

int list_contains(List_t *self, int data) {
  return 0;
}
void list_destroy(List_t *self) {
  Node_t *current, *tmp;
  current = self->head;
  while (current) {
    tmp = current->next;
    free(current);
    current = tmp;
  }
}

size_t list_size(const List_t *self) {
  size_t size = 0;
  Node_t *current = self->head;
  while (current) {
    size++;
    current = current->next;
  }
  return size;
}


