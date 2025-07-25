#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "SongNode.h"    // Required for the SongNode struct definition
#include "RecentPlays.h" // Required for the RecentPlays class (for playSong method)
#include <string>        
#include <vector>        

using namespace std; 
// The Playlist class manages the collection of songs using a Circular Doubly Linked List.
// It provides methods for adding, deleting, displaying, playing, and sorting songs.
class Playlist {
private:
    SongNode* head;   // Pointer to the first song node in the circular list
    SongNode* tail;   // Pointer to the last song node in the circular list
    int songCount;    // Keeps track of the total number of songs in the playlist

     // --- Private Helper Methods for Merge Sort ---
    // Finds the middle node of a linked list (used for splitting in merge sort).
    SongNode* getMiddle(SongNode* node);

    // Merges two sorted linked lists into a single sorted linked list.
    SongNode* merge(SongNode* a, SongNode* b);

    // Recursive function to perform merge sort on a linked list.
    // Returns the head of the sorted sub-list.
    SongNode* mergeSort(SongNode* node);
    

public:
    // Constructor: Initializes an empty playlist.
    Playlist();

    // Destructor: Frees all memory allocated for the song nodes to prevent memory leaks.
    ~Playlist();

    // Adds a new song to the end of the playlist.
    // Parameters:
    //   songName: The name of the song to add.
    void addSong(const string& songName);

    // Deletes a song from the playlist by its name.
   
    void deleteSong(const string& songName);

    // Displays all songs currently in the playlist in their current order.
    void displayPlaylist();

    // Returns the total number of songs in the playlist.
    int getSongCount();

    // Searches for a song in the playlist by name.
    // Parameters:
    //   songName: The name of the song to search for.
    // Returns:
    //   true if the song is found, false otherwise.
    bool searchSong(const string& songName);

    // Simulates playing a song. If found, it adds the song to the recent plays list.
    // Parameters:
    //   songName: The name of the song to play.
    //   recentPlays: A reference to the RecentPlays object to update history.
    void playSong(const string& songName, RecentPlays& recentPlays);

    // Sorts the playlist alphabetically by song name.
    void sortAlphabetically();

    // Loads songs from a specified text file into the playlist.
    // Parameters:
    //   filename: The name of the file to load songs from (e.g., "playlist.txt").
    void loadFromFile(const string& filename);

    // Saves the current playlist (all song names) to a specified text file.
    // Parameters:
    //   filename: The name of the file to save songs to (e.g., "playlist.txt").
    void saveToFile(const string& filename);
};

#endif // PLAYLIST_H