#include "RecentPlays.h" // Include the header for the RecentPlays class
#include <iostream>      
#include <algorithm>     

using namespace std; 

// Implements the addRecent method for the RecentPlays class.
// This method adds a song to the list of recently played tracks,
// ensuring no duplicates and maintaining a fixed maximum size.
void RecentPlays::addRecent(const string& songName) {
    // 1. Check for duplicates:
    // Use std::find to search if the songName already exists in the recentTracks vector.
    auto it = find(recentTracks.begin(), recentTracks.end(), songName);

    // If the song is found (it is not recentTracks.end()), remove the old entry.
    // This ensures that if a song is played again, it moves to the most recent position
    // instead of creating a duplicate entry.
    if (it != recentTracks.end()) {
        recentTracks.erase(it);
    }

    // 2. Add the new song to the front:
    // Insert the songName at the beginning of the vector. This simulates
    // pushing an element onto the top of a stack, making it the most recent.
    recentTracks.insert(recentTracks.begin(), songName);

    // 3. Enforce maximum size:
    // If the number of recent tracks exceeds the defined MAX_SIZE,
    // remove the oldest song (which is at the back of the vector).
    if (recentTracks.size() > MAX_SIZE) {
        recentTracks.pop_back(); // Removes the last element
    }
}

// Implements the displayRecent method for the RecentPlays class.
// This method prints all songs currently stored in the recent tracks list.
void RecentPlays::displayRecent() {
    // Check if the recent tracks list is empty.
    if (recentTracks.empty()) {
        cout << "\n\a\a\a\a=>NO recently played tracks.\n"; 
        return; 
    }

    // Display a header indicating the purpose and size limit of the list.
    cout << "\n\a\a\a\a#Recently played tracks (max " << MAX_SIZE << "):\n";
    
    // Iterate through the vector and print each song name.
    // The songs are displayed from most recent to oldest 
    for (const auto& song : recentTracks) {
        cout << song << "\n";
    }
}

// Implements the getLastPlayed method for the RecentPlays class.
// This method returns the name of the most recently played song.
string RecentPlays::getLastPlayed() {
    // Check if the recent tracks list is empty.
    if (recentTracks.empty()) {
        cout << "\n\a\a\a\a#NO last played tracks.\n"; 
        return ""; 
    }
    // The most recently played song is always at the front of the vector.
    cout << "\n=>Last Played Song - " << recentTracks.front() << "\n";
    return recentTracks.front(); 
}