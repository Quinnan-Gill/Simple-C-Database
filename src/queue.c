#include "queue.h"

void init(Queue *q) {
  q->front = NULL;
  q->last = NULL;
  q->size = 0;
}

int front(Queue *q) {
  return q->front->data;
}

void pop(Queue *q) {
  q->size--;

  struct QueueNode *tmp = q->front;
  q->front = q->front->next;
  free(tmp);
}

void push(Queue *q, uint32_t data) {
  q->size++;

  if (q->front == NULL) {
    q->front =  (struct QueueNode *) malloc(sizeof(struct QueueNode));
    q->front->data = data;
    q->front->next = NULL;
    q->last = q->front;
  } else {
    q->last->next = (struct QueueNode *) malloc(sizeof(struct QueueNode));
    q->last->next->data = data;
    q->last->next->next = NULL;
    q->last = q->last->next;
  }
}

bool empty(Queue *q) {
  return q->size == 0;
}