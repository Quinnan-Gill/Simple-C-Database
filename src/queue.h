#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define DATA_T uint32_t

typedef struct {
    DATA_T data;
    bool endln;
} DataCapsule;

struct QueueNode {
    DataCapsule *data;
    struct QueueNode *next;
};

typedef struct {
    struct QueueNode *front;
    struct QueueNode *last;
    unsigned int size;
} Queue;

void init(Queue *q);

DataCapsule* front(Queue *q);

void pop(Queue *q);

void push(Queue *q, DataCapsule *data);

void push_deconstructed(Queue *q, DATA_T data, bool endln);

bool empty(Queue *q);

#endif