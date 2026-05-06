#ifndef GRAPH_H
#define GRAPH_H

#include "song.h"

#define MAX_SONGS 100

typedef struct Graph {
    AdjNode* adjList[MAX_SONGS];
    int size;
} Graph;

Graph* createGraph();
void addEdge(Graph* graph, int src, int dest);
void connectSimilarSongs(Graph* graph, Node* head);
void bfsRecommend(Graph* graph, Node* head, int startId);
void freeGraph(Graph* graph);

#endif