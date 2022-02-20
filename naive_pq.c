#include <malloc.h>
#include <stdio.h>
#include "naive_pq.h"

void push(pqueue **head, int _value, void* _object) {
	pqueue *right = *head;
	pqueue *left = NULL;
	while(right != NULL && right->value > _value) { //skokame pogolemi
		left = right;
		right = right->next;
	}
	pqueue *new_element = malloc(sizeof(pqueue));
	new_element->next = right;
	new_element->object = _object;
	new_element->value = _value;

	if (left) left->next = new_element;
	else *head = new_element; //ako nisto ne sme preskoknale, noviot element e prviot...
}
void* pop(pqueue **head) {
	if (!(*head)) return NULL;
	pqueue *res = (*head)->object;
	pqueue *prev = *head;
	*head = (*head)->next;
	free(prev);
	return res;
}
