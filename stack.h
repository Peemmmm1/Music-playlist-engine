#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createStack() {
    Stack* stack = (Stack)malloc(sizeof(Stack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack stack, Song song) {
    StackNode* newNode = (StackNode)malloc(sizeof(StackNode));
    newNode->song = song;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

Song pop(Stack stack) {
    if (isStackEmpty(stack)) {
        printf("History is empty\n");
        Song empty = {0};
        return empty;
    }
    StackNode* temp = stack->top;
    Song song = temp->song;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return song;
}

int isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}

void freeStack(Stack* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}
Peem — 3/5/69 22:56
stack.c
#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "song.h"

int getTotalWeight(Node* head);
Node* weightedShuffle(Node* head);
void incrementPlayCount(Node* head, int id);

#endif