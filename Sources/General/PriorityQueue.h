#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

// Originally from: http://rosettacode.org/wiki/Priority_queue#C

typedef struct Payload Payload;

struct Payload
{
  void* data;
  int priority;
};

typedef struct Queue Queue;

struct Queue
{
  Payload* buffer;
  int n;
  int alloc;
};

Queue* priq_new(int size);

int priq_size(Queue* q);

void priq_push(Queue* q, void *data, int pri);

/* remove top item. returns 0 if empty. *pri can be null. */
void* priq_pop(Queue* q, int *pri);

/* get the top element without removing it from queue */
void* priq_top(Queue* q, int *pri);

/* this is O(n log n), but probably not the best */
void priq_combine(Queue* q, Queue* q2);

#endif
