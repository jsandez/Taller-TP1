#ifndef _LIST_H_
#define _LIST_H_

struct Node;
typedef struct Node Node_t;
struct Node {
  int data;
  Node_t *next;
};

typedef struct list {
  Node_t *head;
} List_t;

void list_create(List_t *self);
void list_add(List_t *self, int data);
int list_contains(List_t *self, int data);
size_t list_size(const List_t *self);
void list_destroy(List_t *self);

#endif
