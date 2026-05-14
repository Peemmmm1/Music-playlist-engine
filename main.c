#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "song.h"
#include "linked_list.h"
#include "hash_table.h"
#include "stack.h"
#include "shuffle.h"
#include "graph.h"

int nextId = 1;
Node* currentSong = NULL;

void addNewSong(Node** head, HashTable* ht, Graph* graph) {
    Song song;
    song.id = nextId++;
    song.play_count = 0;
    printf("Title: "); scanf(" %[^\n]", song.title);
    printf("Artist: "); scanf(" %[^\n]", song.artist);
    printf("Genre: "); scanf(" %[^\n]", song.genre);
    printf("Duration (sec): "); scanf("%d", &song.duration);
    printf("YouTube URL: "); scanf(" %[^\n]", song.url); // เพิ่มตรงนี้
    addSong(head, song);
    insertHash(ht, song);
    connectSimilarSongs(graph, *head);
    printf("Song added!\n");
}

void playSong(Node** current, Stack* history) {
    if (*current == NULL) {
        printf("No song playing\n");
        return;
    }
    push(history, (*current)->song);
    incrementPlayCount(*current, (*current)->song.id);
    printf("Now playing: %s - %s\n",
        (*current)->song.title,
        (*current)->song.artist);
}

int main() {
    Node* head = NULL;
    HashTable* ht = createHashTable();
    Stack* history = createStack();
    Graph* graph = createGraph();
    int choice;

    while (1) {
        printf("\n=== Music Playlist Engine ===\n");
        printf("1. Add song\n");
        printf("2. Delete song\n");
        printf("3. Display playlist\n");
        printf("4. Play current song\n");
        printf("5. Next song\n");
        printf("6. Previous song\n");
        printf("7. Shuffle\n");
        printf("8. Search song\n");
        printf("9. Recommend songs\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1:
                addNewSong(&head, ht, graph);
                if (currentSong == NULL) currentSong = head;
                break;
            case 2: {
                int id;
                printf("Enter song ID to delete: ");
                scanf("%d", &id);
                deleteSong(&head, id);
                break;
            }
            case 3:
                displayPlaylist(head);
                break;
            case 4:
                playSong(&currentSong, history);
                break;
            case 5:
                if (currentSong != NULL) {
                    push(history, currentSong->song);
                    currentSong = playNext(currentSong);
                    printf("Now playing: %s\n", currentSong->song.title);
                }
                break;
            case 6:
                if (!isStackEmpty(history)) {
                    Song prev = pop(history);
                    printf("Back to: %s\n", prev.title);
                }
                break;
            case 7: {
                Node* shuffled = weightedShuffle(head);
                if (shuffled != NULL) {
                    currentSong = shuffled;
                    printf("Shuffled to: %s - %s\n",
                        shuffled->song.title,
                        shuffled->song.artist);
                }
                break;
            }
            case 8: {
                char title[MAX_TITLE];
                printf("Enter song title: ");
                scanf(" %[^\n]", title);
                Song* found = searchHash(ht, title);
                if (found) {
                    printf("Found: %s - %s (%s)\n",
                        found->title, found->artist, found->genre);
                } else {
                    printf("Song not found\n");
                }
                break;
            }
            case 9:
                if (currentSong != NULL) {
                    bfsRecommend(graph, head, currentSong->song.id);
                } else {
                    printf("No song playing\n");
                }
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    freeHashTable(ht);
    freeStack(history);
    freeGraph(graph);
    return 0;
}
