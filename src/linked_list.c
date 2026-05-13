#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

Node* createNode(Song song) {
    Node* newNode = (Node)malloc(sizeof(Node));
    newNode->song = song;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addSong(Node** head, Song song) {
    Node newNode = createNode(song);
    if (*head == NULL) {
        head = newNode;
        return;
    }
    Node temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteSong(Node** head, int id) {
    Node temp = head;
    while (temp != NULL && temp->song.id != id) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Song not found\n");
        return;
    }
    if (temp->prev != NULL) temp->prev->next = temp->next;
    elsehead = temp->next;
    if (temp->next != NULL) temp->next->prev = temp->prev;
    free(temp);
}

void displayPlaylist(Node* head) {
    Node* temp = head;
    int i = 1;
    while (temp != NULL) {
        printf("%d. [%d] %s - %s (%s) | %d sec\n",
            i++, temp->song.id, temp->song.title,
            temp->song.artist, temp->song.genre,
            temp->song.duration);
        temp = temp->next;
    }
}

Node* playNext(Node* current) {
    if (current->next != NULL) return current->next;
    printf("End of playlist\n");
    return current;
}

Node* playPrev(Node* current) {
    if (current->prev != NULL) return current->prev;
    printf("Already at beginning\n");
    return current;
}
