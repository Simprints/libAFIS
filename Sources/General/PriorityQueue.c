#include "General/PriorityQueue.h"

#include <stdlib.h>

#define priq_purge(q) (q)->n = 1

/* first element in array not used to simplify indices */
Queue* priq_new(int size)
{
  if (size < 4) size = 4;

  Queue* q = malloc(sizeof(Queue));
  q->buffer = malloc(sizeof(Payload) * size);
  q->alloc = size;
  q->n = 1;

  return q;
}

int priq_size(Queue* q) {
  return (q->n) - 1;
}

void priq_push(Queue* q, void *data, int pri)
{
  Payload *b;
  int n, m;

  if (q->n >= q->alloc) {
    q->alloc *= 2;
    b = q->buffer = realloc(q->buffer, sizeof(Payload) * q->alloc);
  } else
    b = q->buffer;

  n = q->n++;
  /* append at end, then up heap */
  while ((m = n / 2) && pri < b[m].priority) {
    b[n] = b[m];
    n = m;
  }
  b[n].data = data;
  b[n].priority = pri;
}

/* remove top item. returns 0 if empty. *pri can be null. */
void * priq_pop(Queue* q, int *pri)
{
  void *out;
  if (q->n == 1) return 0;

  Payload *b = q->buffer;

  out = b[1].data;
  if (pri) *pri = b[1].priority;

  /* pull last item to top, then down heap. */
  --q->n;

  int n = 1, m;
  while ((m = n * 2) < q->n) {
    if (m + 1 < q->n && b[m].priority > b[m + 1].priority) m++;

    if (b[q->n].priority <= b[m].priority) break;
    b[n] = b[m];
    n = m;
  }

  b[n] = b[q->n];
  if (q->n < q->alloc / 2 && q->n >= 16)
    q->buffer = realloc(q->buffer, (q->alloc /= 2) * sizeof(b[0]));

  return out;
}

/* get the top element without removing it from queue */
void* priq_top(Queue* q, int *pri)
{
  if (q->n == 1) return 0;
  if (pri) *pri = q->buffer[1].priority;
  return q->buffer[1].data;
}

/* this is O(n log n), but probably not the best */
void priq_combine(Queue* q, Queue* q2)
{
  int i;
  Payload *e = q2->buffer + 1;

  for (i = q2->n - 1; i >= 1; i--, e++)
    priq_push(q, e->data, e->priority);
  priq_purge(q2);
}
