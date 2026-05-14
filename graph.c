#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_SONGS; i++) {
        graph->adjList[i] = NULL;
    }
    graph->size = 0;
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjNode* newNode = (AdjNode*)malloc(sizeof(AdjNode));
    newNode->song_id = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    AdjNode* newNode2 = (AdjNode*)malloc(sizeof(AdjNode));
    newNode2->song_id = src;
    newNode2->next = graph->adjList[dest];
    graph->adjList[dest] = newNode2;
}

void connectSimilarSongs(Graph* graph, Node* head) {
    Node* i = head;
    while (i != NULL) {
        Node* j = i->next;
        while (j != NULL) {
            if (strcmp(i->song.genre, j->song.genre) == 0 ||
                strcmp(i->song.artist, j->song.artist) == 0) {
                addEdge(graph, i->song.id, j->song.id);
            }
            j = j->next;
        }
        i = i->next;
    }
}

void bfsRecommend(Graph* graph, Node* head, int startId) {
    int visited[MAX_SONGS] = {0};
    int queue[MAX_SONGS];
    int front = 0, rear = 0;

    visited[startId] = 1;
    queue[rear++] = startId;

    printf("Recommended songs:\n");
    int found = 0;

    while (front < rear) {
        int current = queue[front++];
        AdjNode* temp = graph->adjList[current];
        while (temp != NULL) {
            if (!visited[temp->song_id]) {
                visited[temp->song_id] = 1;
                queue[rear++] = temp->song_id;

                Node* n = head;
                while (n != NULL) {
                    if (n->song.id == temp->song_id) {
                        printf("- %s by %s (%s)\n",
                            n->song.title,
                            n->song.artist,
                            n->song.genre);
                        found++;
                        break;
                    }
                    n = n->next;
                }
            }
            temp = temp->next;
        }
        if (found >= 3) break;
    }
    if (found == 0) printf("No recommendations found\n");
}

void freeGraph(Graph* graph) {
    for (int i = 0; i < MAX_SONGS; i++) {
        AdjNode* temp = graph->adjList[i];
        while (temp != NULL) {
            AdjNode* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
}