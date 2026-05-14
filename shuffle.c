#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

int getTotalWeight(Node* head) {
    int total = 0;
    Node* temp = head;
    while (temp != NULL) {
        total += (temp->song.play_count + 1);
        temp = temp->next;
    }
    return total;
}

Node* weightedShuffle(Node* head) {
    if (head == NULL) return NULL;

    srand(time(NULL));
    int total = getTotalWeight(head);
    int random = rand() % total;

    Node* temp = head;
    int cumulative = 0;
    while (temp != NULL) {
        cumulative += (temp->song.play_count + 1);
        if (random < cumulative) return temp;
        temp = temp->next;
    }
    return head;
}

void incrementPlayCount(Node* head, int id) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->song.id == id) {
            temp->song.play_count++;
            return;
        }
        temp = temp->next;
    }
}