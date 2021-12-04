//
// Created by Aleksandar on 04-Dec-21.
//

#ifndef C_VEZBI_QUEUE_H
#define C_VEZBI_QUEUE_H

#include <malloc.h>
struct queue {
    int num;
    struct queue* next;
} first;
void add(int n) {
    static struct queue *head = &first;
    head->num = n;
    head->next = malloc(sizeof(struct queue));
    //se premestuvame napred i postavuvame granicnik
    head = head->next;
    head->next = NULL;
}
static struct queue* curr = &first;
int pop() {
    int result = curr->num;
    curr = curr->next;
    return result;
}

#endif //C_VEZBI_QUEUE_H
