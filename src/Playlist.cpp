#include "Playlist.h" // Include the header for the Playlist class
#include <iostream>   
#include <fstream>    // Required for file operations 
#include <algorithm>  

using namespace std; 

// Constructor for the Playlist class.
// Initializes the head and tail pointers to nullptr and songCount to 0,
// indicating an empty playlist upon creation.
Playlist::Playlist(){
    head = nullptr;
    tail = nullptr;
    songCount = 0;
} 

// Destructor for the Playlist class.
// This is crucial for memory management. It iterates through the circular
// doubly linked list and deallocates memory for each SongNode to prevent leaks.
Playlist::~Playlist() {
    if (head == nullptr) { // If the playlist is empty, there's nothing to delete.
        return;
    }

    // Start from the node after head to avoid deleting head prematurely
    // in a circular list, and to correctly handle the loop condition.
    SongNode* curr = head->next;
    while (curr != head) { // Loop until we come back to the head
        SongNode* temp = curr; // Store current node to delete
        curr = curr->next;  // Move to the next node before deleting current
        delete temp;              // Deallocate memory for the stored node
    }
    delete head; // Finally, delete the head node
    head = tail = nullptr; // Reset pointers to indicate an empty list
    songCount = 0;         // Reset song count
}

// Adds a new song to the end of the circular doubly linked list.
// Handles both empty list case and adding to an existing list.
void Playlist::addSong(const string& songName) {
    SongNode* newNode = new SongNode(songName); 

    if (head == nullptr) { // Playlist is empty
        head = tail = newNode; // New node is both head and tail
        head->next = head;     // It points to itself (circular)
        head->prev = head;     // It points to itself (doubly circular)
    } 
    else { 
        newNode->prev = tail;  // New node's previous points to current tail
        newNode->next = head;  // New node's next points to current head 
        tail->next = newNode;  // Current tail's next points to new node
        head->prev = newNode;  // Current head's previous points to new node
        tail = newNode;        // New node becomes the new tail
    }
    songCount++; // Increment the total song count
    cout << "\n\a\a\a\aSong '" << songName << "' added.\n";
}

// Deletes a song from the playlist by its name.
// Handles various cases: empty list, single-node list, head, tail, or middle node deletion.
void Playlist::deleteSong(const string& songName) {
    if (head == nullptr) { // If playlist is empty, cannot delete
        cout << "\nPlaylist is empty. Cannot delete.\n";
        return;
    }

    SongNode* curr = head;
    // Iterate through the circular list to find the song
    for (int i = 0; i < songCount; ++i) {
        if (curr->songName == songName) { // Song found
            if (songCount == 1) { //Only one song in the playlist
                delete head;      
                head = tail = nullptr; 
            }
            else { 
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;

                if (curr == head) { 
                    head = curr->next; 
                }

                if (curr == tail) { 
                    tail = curr->prev;
                }
                delete curr; 
            }

            songCount--; 
            cout << "\n\a\a\a\aSong '" << songName << "' has been deleted.\n";
            saveToFile("playlist.txt"); // Save changes to file immediately after deletion
            return; 
        }
        curr = curr->next; 
    }

    // If loop finishes, song was not found
    cout << "\n\a\a\a\aSong '" << songName << "' not found.\n";
}

// Displays all songs currently in the playlist.
// Traverses the circular list from head and prints each song name.
void Playlist::displayPlaylist() {
    if (head == nullptr) { // If playlist is empty
        cout << "\nPlaylist is empty.\n";
        return;
    }
    cout << "\nPlaylist:\n";
    SongNode* curr = head;

// IF WE USE WHILE LOOP here, Then if curr == head at the start, the loop won’t run at all, meaning nothing gets printed — even though there's data in the list.

    do { // Use do-while loop for circular list to ensure head is printed at least once
        cout << curr->songName << "\n";
        curr = curr->next; 
    } while (curr != head); 
}

// Returns the total number of songs in the playlist.

int Playlist::getSongCount() {
    return songCount;
}

// Searches for a song in the playlist by name.
// Returns true if the song is found, false otherwise.
bool Playlist::searchSong(const string& songName) {
    if (head == nullptr) { // If playlist is empty, song cannot be found
        return false;
    }

    SongNode* current = head;
    // Iterate through the circular list to find the song
    for (int i = 0; i < songCount; ++i) {
        if (current->songName == songName) { // Song found
            return true;
        }
        current = current->next; // Move to the next node
    }
    
    return false; // Song not found
}

// Simulates playing a song. If the song is found in the playlist,
// it is marked as "Now Playing" and added to the RecentPlays history.
void Playlist::playSong(const string& songName, RecentPlays& recentPlays) {
    if (head == nullptr) { // If playlist is empty, no songs to play
        cout << "\nPlaylist is empty. Cannot play song.\n";
        return;
    }

    SongNode* current = head;
    bool found = false;
    // Iterate through the circular list to find the song
    for (int i = 0; i < songCount; ++i) {
        if (current->songName == songName) { // Song found
            found = true;
            break;
        }
        current = current->next; // Move to the next node
    }

    if (found) {
        cout << "\n\a\a\a\a=> Now Playing... " << songName << "\n";
        recentPlays.addRecent(songName); // Add the played song to recent history
    } else {
        cout << "\n\a\a\a\a#Song '" << songName << "' not found in the playlist.\n";
    }
}

// Sorts the playlist alphabetically by song name using a merge Sort algorithm.
// This implementation swaps the 'songName' data within the nodes, rather than re-linking nodes.

SongNode* Playlist::getMiddle(SongNode* node) {
    if (node == nullptr || node->next == node) { // Empty or single node list
        return node;
    }

    SongNode* slow = node;
    SongNode* fast = node->next; // Start fast one step ahead to correctly find middle for splitting

    // Move fast by two, slow by one. When fast reaches end, slow is at middle.
    // For circular list, we need to break the cycle temporarily.
    // This function assumes a non-circular list for splitting.
    // We will make the list non-circular before calling this.
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Merges two sorted linked lists into a single sorted linked list.
// This function assumes the input lists 'a' and 'b' are non-circular and sorted. It also correctly handles the 'prev' pointers for the merged list.
SongNode* Playlist::merge(SongNode* a, SongNode* b) {
    // Base cases for recursion
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    SongNode* result = nullptr;

    // Pick either 'a' or 'b', and recur
    if (a->songName <= b->songName) {
        result = a;
        result->next = merge(a->next, b);
        if (result->next != nullptr) { // Update prev pointer for the merged part
            result->next->prev = result;
        }
    } else {
        result = b;
        result->next = merge(a, b->next);
        if (result->next != nullptr) { // Update prev pointer for the merged part
            result->next->prev = result;
        }
    }
    return result;
}

SongNode* Playlist::mergeSort(SongNode* node) {
    // Base case: if list is empty or has one node, it's already sorted
    if (node == nullptr || node->next == nullptr) { // Changed from node->next == node for non-circular
        return node;
    }

    // Find the middle of the list
    SongNode* middle = getMiddle(node);
    SongNode* nextOfMiddle = middle->next;

    // Break the list into two halves
    middle->next = nullptr; // First half ends here
    if (nextOfMiddle != nullptr) {
        nextOfMiddle->prev = nullptr; // Second half starts here
    }

    // Recursively sort the two halves
    SongNode* left = mergeSort(node); // Pass 'node' as head of left half
    SongNode* right = mergeSort(nextOfMiddle);

    // Merge the sorted halves
    SongNode* sortedHead = merge(left, right);

    return sortedHead;
}

void Playlist::sortAlphabetically() {
    if (head == nullptr || head->next == head) { // 0 or 1 song, already sorted
        cout << "\nPlaylist has 0 or 1 song, no sorting needed.\n";
        return;
    }

    // Temporarily break circularity for sorting
    SongNode* originalTail = head->prev;
    originalTail->next = nullptr; // Break link from tail to head
    head->prev = nullptr;         // Break link from head to tail

    // Perform the merge sort
    head = mergeSort(head);

    // Re-establish circularity for the sorted list
    // Find the new tail after sorting
    SongNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    tail = current; // The last node is the new tail

    tail->next = head; // Link tail to head
    head->prev = tail; // Link head to tail

    cout << "\nPlaylist sorted alphabetically using Merge Sort.\n";
}

// Loads songs from a specified text file into the playlist.
// Each line in the file is treated as a song name.
void Playlist::loadFromFile(const string& filename) {
    ifstream file(filename); // Open the file for reading
    if (!file.is_open()) { // Check if file opening failed
        cout << "\nNo existing playlist file found. Starting with an empty playlist.\n";
        return;
    }

    // Clear existing playlist before loading from file to prevent duplicates
    // This is important if loadFromFile is called multiple times or on a non-empty list.
    // Call the destructor logic to clear current nodes
    if (head != nullptr) {
        SongNode* current = head->next;
        while (current != head) {
            SongNode* temp = current;
            current = current->next;
            delete temp;
        }
        delete head;
        head = tail = nullptr;
        songCount = 0;
    }

    string songName;
    while (getline(file, songName)) { // Read file line by line
        if (!songName.empty()) { // Ensure the line is not empty
            addSong(songName); // Add each read song name to the playlist
        }
    }
    file.close(); // Close the file
    cout << "\nPlaylist loaded from file.\n";
}

// Saves the current playlist (all song names) to a specified text file.
// This overwrites the file with the current state of the playlist.
void Playlist::saveToFile(const string& filename) {
    ofstream file(filename); // Open the file for writing (this truncates/clears it)
    if (!file.is_open()) { // Check if file opening failed
        cerr << "Error: Could not open file '" << filename << "' for saving.\n";
        return;
    }

    if (head == nullptr) { // If playlist is empty, just close the file (it will be empty)
        file.close();
        return;
    }

    SongNode* current = head;
    do { // Traverse the circular list and write each song name to the file
        file << current->songName << "\n";
        current = current->next;
    } while (current != head);
    
    file.close(); // Close the file
}