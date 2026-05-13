#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "song.h"

#define TABLE_SIZE 100

typedef struct HashEntry {
    char key[MAX_TITLE];
    Song song;
    struct HashEntry* next;
} HashEntry;

typedef struct {
    HashEntry* buckets[TABLE_SIZE];
} HashTable;

HashTable* createHashTable();
void insertHash(HashTable* ht, Song song);
Song* searchHash(HashTable* ht, char* title);
void deleteHash(HashTable* ht, char* title);
void freeHashTable(HashTable* ht);

#endif

