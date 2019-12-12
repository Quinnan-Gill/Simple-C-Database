#include "queue.h"

void init(Queue *q) {
    q->front = NULL;
    q->last = NULL;
    q->size = 0;
}

DataCapsule* front(Queue *q) {
    return q->front->data;
}

void pop(Queue *q) {
    q->size--;

    struct QueueNode *tmp = q->front;
    q->front = q->front->next;
    free(tmp->data);
    free(tmp);
}

void push(Queue *q, DataCapsule *data) {
    q->size++;
    
    if (q->front == NULL) {
        q->front = (struct QueueNode *) malloc(sizeof(struct QueueNode));
        q->front->data = data;
        q->front->next = NULL;
        q->last = q->front;
    } else {
        q->last->next = (struct QueueNode *) malloc(sizeof(struct  QueueNode));
        q->last->next->data = data;
        q->last->next->next = NULL;
        q->last = q->last->next;
    }
}

void push_deconstructed(Queue *q, DATA_T data, bool endln) {
    DataCapsule *dataCap = (DataCapsule *) malloc(sizeof(DataCapsule));
    dataCap->data = data;
    dataCap->endln = endln;

    push(q, dataCap);
}

bool empty(Queue *q) {
    return q->size == 0;
}