# Music Playlist Engine

**CPE112: Programming with Data Structures — Final Project (2/2025)**

A CLI-based music playlist management system that simulates how real streaming platforms (Spotify, YouTube Music) work under the hood — built in C using four core data structures.

---

## Team Members

1.Chawakorn Rungrueng ID: 68070503486 (GitHub: chawakornpukan-pixel)
— Linked List + Hash Table

2.Supakrit Kositwiwat ID: 68070503491 (GitHub: Peemmmm1)
- Graph + BFS + Menu

3.Sutharos Siriton ID:68070503492 (GitHub: sutharos31-ops)
- Stack + Weighted Shuffle

**Commit Hash:** `5e914ce`

---

## Problem Description

Modern music listeners manage hundreds of songs but lack efficient tools to navigate playlists quickly, search songs instantly, undo accidental skips, or get smart recommendations. This project solves those problems by implementing the core engine of a music player using fundamental data structures.

---

##  Data Structures Used

Doubly Linked
-ListPlaylist navigation (next/prev/jump)
-O(1) next/prev

Stack (LIFO)
-Play history & undo
-O(1) push/pop

Hash Table
-Search song by title
-O(1) average

Graph + BFS
-Song recommendation
-O(V + E)

## Why each structure?

- **Doubly Linked List** — Unlike arrays, inserting/deleting is O(1). Unlike singly linked list, `prev()` is O(1) instead of O(n).
- **Stack** — LIFO perfectly models "undo last play". Queue would give oldest song first — wrong for undo.
- **Hash Table** — O(1) average search vs O(n) linear scan through the list.
- **Graph + BFS** — Songs form a similarity network. BFS gives nearest matches first, better UX than DFS.

---

## Algorithms

# Weighted Shuffle
Each song gets `weight = play_count + 1`. Songs played more often have a proportionally larger slot in the cumulative weight array, giving them a higher chance of being selected — the same idea behind Spotify's Smart Shuffle.

# BFS 
Builds a similarity graph where songs share an edge if they have the same genre or artist. BFS from the currently playing song returns related songs with closest matches appearing first.

---

## Project Structure

```
Music-playlist-engine/
├── song.h           ← Song struct + Node/StackNode/AdjNode definitions
├── linked_list.h/c  ← Doubly Linked List (playlist navigation)
├── stack.h/c        ← Stack (play history & undo)
├── hash_table.h/c   ← Hash Table (fast search)
├── graph.h/c        ← Graph + BFS (recommendations)
├── shuffle.h/c      ← Weighted Shuffle algorithm
├── main.c           ← Menu-driven interface
└── README.md




## How to Run

### Requirements
- GCC compiler with C11 support

### Compile
```bash
gcc main.c linked_list.c hash_table.c stack.c graph.c shuffle.c -o main
```

### Run
```bash
./main
```

---

## Menu Options

```
=== Music Playlist Engine ===
1.  Add song
2.  Delete song
3.  Display playlist
4.  Play current song      ← opens YouTube URL in browser
5.  Next song
6.  Previous song
7.  Shuffle                ← weighted by play count
8.  Search song            ← O(1) hash table lookup
9.  Recommend songs        ← BFS on similarity graph
10. Jump to song           ← go directly to any song by ID
0.  Exit
```

---

## Sample Input / Output

**Adding and playing a song:**
```
Choice: 1
Title: Blinding Lights
Artist: The Weeknd
Genre: Pop
Duration (sec): 200
YouTube URL: https://www.youtube.com/watch?v=4NRXx6U8ABQ
Song added!

Choice: 4
Now playing: Blinding Lights - The Weeknd
```

**BFS Recommendation:**
```
Choice: 9
Recommended songs:
- Save Your Tears by The Weeknd (Pop)
- Shape of You by Ed Sheeran (Pop)
```

**Jump to Song:**
```
Choice: 10
1. [1] Blinding Lights - The Weeknd (Pop) | 200 sec
2. [2] Save Your Tears - The Weeknd (Pop) | 215 sec
3. [3] Shape of You - Ed Sheeran (Pop)    | 234 sec
Enter song ID to jump to: 3
Now playing: Shape of You - Ed Sheeran
```

---

##  Notes

- YouTube URL field supports any valid URL — pressing Play (menu 4) opens it in your default browser automatically
- Cross-platform: uses `start` on Windows, `open` on macOS, `xdg-open` on Linux
- Play history is session-only — data is not saved after exiting
- Maximum 99 songs per session (defined by `MAX_SONGS`)