#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

struct QueueNode{
    uint32_t data;
    struct QueueNode *next;
};

typedef struct {
    struct QueueNode *front;
    struct QueueNode *last;
    unsigned int size;
} Queue;

void init(Queue *q);

int front(Queue *q);

void pop(Queue *q);

void push(Queue *q, uint32_t data);

bool empty(Queue *q);

#endif