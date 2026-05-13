#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "song.h"

int getTotalWeight(Node* head);
Node* weightedShuffle(Node* head);
void incrementPlayCount(Node* head, int id);

#endif