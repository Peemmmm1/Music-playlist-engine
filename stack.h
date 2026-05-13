#ifndef STACK_H
#define STACK_H

#include "song.h"

typedef struct Stack {
    StackNode* top;
    int size;
} Stack;

Stack* createStack();
void push(Stack* stack, Song song);
Song pop(Stack* stack);
int isStackEmpty(Stack* stack);
void freeStack(Stack* stack);

#endif