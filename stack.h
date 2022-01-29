//STACK.H
#ifndef STACK_H
#define STACK_H

typedef struct stack_int stack;

int peek(stack* a);
stack* pop(stack* a);
stack* push(stack* a, int n);
stack* erase(stack* a);
#endif // STACK_H
