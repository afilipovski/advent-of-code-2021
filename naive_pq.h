#ifndef NAIVE_PQ_H
#define NAIVE_PQ_H

typedef struct pqueue {
	int value;
	void *object;
	struct pqueue *next;
} pqueue;
extern void push(pqueue **head, int _value, void* _object);
extern void* pop(pqueue **head);
#endif // NAIVE_PQ_H
