#include "stack.h"
#include<malloc.h>

struct stack_int {
    int data;
    struct stack_int* previous;
};
int peek(stack* a) {
    if (a)
        return a->data;
    else return 0;
}
stack* pop(stack* a) {
    if (!a) return 0;
    stack* paddress = a->previous;
    free(a);
    return paddress;
}
stack* push(stack* a, int n) {
    stack* newelement = malloc(sizeof(stack));
    newelement -> data = n;
    newelement -> previous = a;
    return newelement;
}
stack* erase(stack* a) {
    while(a)
        a = pop(a);
    return a;
}
