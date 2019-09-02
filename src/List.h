#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
  int data;
  struct node *next;
} node_t;

typedef struct list {
  struct node *head;
} list_t;

void list_create(list_t *self);
void list_add(list_t *self, int data);
int list_contains(list_t *self, int data);
size_t list_size(const list_t *self);
void list_destroy(list_t *self);

#endif
