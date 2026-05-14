#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "song.h"

Node* createNode(Song song);
void addSong(Node** head, Song song);
void deleteSong(Node** head, int id);
void displayPlaylist(Node* head);
Node* playNext(Node* current);
Node* playPrev(Node* current);

#endif