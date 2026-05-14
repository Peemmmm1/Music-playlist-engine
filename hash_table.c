#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int hashFunction(char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash + key[i]) % TABLE_SIZE;
    }
    return hash;
}

HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = NULL;
    }
    return ht;
}

void insertHash(HashTable* ht, Song song) {
    int index = hashFunction(song.title);
    HashEntry* newEntry = (HashEntry*)malloc(sizeof(HashEntry));
    strcpy(newEntry->key, song.title);
    newEntry->song = song;
    newEntry->next = ht->buckets[index];
    ht->buckets[index] = newEntry;
}

Song* searchHash(HashTable* ht, char* title) {
    int index = hashFunction(title);
    HashEntry* temp = ht->buckets[index];
    while (temp != NULL) {
        if (strcmp(temp->key, title) == 0) return &temp->song;
        temp = temp->next;
    }
    return NULL;
}

void deleteHash(HashTable* ht, char* title) {
    int index = hashFunction(title);
    HashEntry* temp = ht->buckets[index];
    HashEntry* prev = NULL;
    while (temp != NULL && strcmp(temp->key, title) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Song not found\n");
        return;
    }
    if (prev == NULL) ht->buckets[index] = temp->next;
    else prev->next = temp->next;
    free(temp);
}

void freeHashTable(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashEntry* temp = ht->buckets[i];
        while (temp != NULL) {
            HashEntry* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(ht);
}