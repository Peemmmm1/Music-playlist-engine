#ifndef SONG_H
#define SONG_H
 
#define MAX_TITLE  100
#define MAX_ARTIST 100
#define MAX_GENRE  50
#define MAX_SONGS  100  
 
typedef struct Song {
    int id;
    char title[MAX_TITLE];
    char artist[MAX_ARTIST];
    char genre[MAX_GENRE];
    char url[200];
    int play_count;
    int duration;
} Song;
 
typedef struct Node {
    Song song;
    struct Node* prev;
    struct Node* next;
} Node;
 
typedef struct StackNode {
    Song song;
    struct StackNode* next;
} StackNode;
 
typedef struct AdjNode {
    int song_id;
    struct AdjNode* next;
} AdjNode;
 
#endif