#include <stdlib.h>
#include "List.h"

void list_create(list_t *self) {
  self->head = NULL;
}
void list_add(list_t *self, int data) {
  struct node *current = self->head;
  struct node *newNode =(struct node *)malloc(sizeof(struct node));
  newNode->data= data;
  newNode->next=NULL;
  if (current == NULL) {
    self->head = newNode;
  } else {
    while (current->next) {
      current = current->next;
    }
    current->next = newNode;
  }
}

int list_contains(list_t *self, int data) {
  return 0;
}
void list_destroy(list_t *self) {
  struct node *current, *tmp;
  current = self->head;
  while (current) {
    tmp = current->next;
    free(current);
    current = tmp;
  }
}

size_t list_size(const list_t *self) {
  size_t size = 0;
  struct node *current = self->head;
  while (current) {
    size++;
    current = current->next;
  }
  return size;
}


