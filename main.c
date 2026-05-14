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
    
    if (nextId >= MAX_SONGS) {
        printf("Playlist full! Maximum %d songs.\n", MAX_SONGS - 1);
        return;
    }
    Song song;
    song.id = nextId++;
    song.play_count = 0;
    printf("Title: ");          scanf(" %[^\n]", song.title);
    printf("Artist: ");         scanf(" %[^\n]", song.artist);
    printf("Genre: ");          scanf(" %[^\n]", song.genre);
    printf("Duration (sec): "); scanf("%d", &song.duration);
    printf("YouTube URL: ");    scanf(" %[^\n]", song.url);
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
    char command[220];
#ifdef _WIN32
    sprintf(command, "start %s", (*current)->song.url);   
#elif __APPLE__
    sprintf(command, "open %s", (*current)->song.url);    
#else
    sprintf(command, "xdg-open %s", (*current)->song.url); 
#endif
    system(command);
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
        printf("10. Jump to song\n");
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
               
                if (currentSong != NULL && currentSong->song.id == id) {
                    if      (currentSong->next != NULL) currentSong = currentSong->next;
                    else if (currentSong->prev != NULL) currentSong = currentSong->prev;
                    else                                currentSong = NULL;
                }
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
                    
                    if (currentSong->next != NULL) {
                        currentSong = playNext(currentSong);
                        playSong(&currentSong, history);
                    } else {
                        printf("Already at last song.\n");
                    }
                }
                break;
 
            case 6: {
               
                int found_prev = 0;
                while (!isStackEmpty(history)) {
                    Song prev = pop(history);
                    if (currentSong == NULL || prev.id != currentSong->song.id) {
                        Node* temp = head;
                        while (temp != NULL) {
                            if (temp->song.id == prev.id) {
                                currentSong = temp;
                                found_prev = 1;
                                break;
                            }
                            temp = temp->next;
                        }
                        if (found_prev) {
                            printf("Back to: %s\n", prev.title);
                            break;
                        }
                    }
                }
                if (!found_prev) printf("No history to go back to\n");
                break;
            }
 
            case 7: {
                Node* shuffled = weightedShuffle(head);
                if (shuffled != NULL) {
                    currentSong = shuffled;
                    printf("Shuffled to: %s - %s\n",
                        shuffled->song.title, shuffled->song.artist);
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
 
            case 10: {
                displayPlaylist(head);
                printf("Enter song ID to jump to: ");
                int jump_id;
                scanf("%d", &jump_id);
                Node* target = head;
                while (target != NULL) {
                    if (target->song.id == jump_id) {
                        currentSong = target;
                        playSong(&currentSong, history);
                        break;
                    }
                    target = target->next;
                }
                if (target == NULL)
                    printf("Song ID %d not found\n", jump_id);
                break;
            }
 
            default:
                printf("Invalid choice\n");
        }
    }
 
    freeHashTable(ht);
    freeStack(history);
    freeGraph(graph);
    return 0;
}