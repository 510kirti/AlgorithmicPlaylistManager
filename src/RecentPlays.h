#ifndef RECENTPLAYS_H
#define RECENTPLAYS_H

#include <string>   
#include <vector>   

using namespace std;

// The RecentPlays class manages a list of recently played songs.
// It acts like a fixed-size stack, keeping only the most recent tracks.
class RecentPlays {
private:
    // vector to store song names for recently played tracks.
    // This vector will behave like a stack where new elements are added to the front.
    vector<string> recentTracks;

    // Defines the maximum number of songs to keep in the recent history.
    // This prevents the list from growing indefinitely.
    const int MAX_SIZE = 10; 

public:
    // Adds a song to the list of recently played tracks.
    // If the song is already present, it's moved to the top (most recent) position.
    // If the list exceeds MAX_SIZE, the oldest song is removed.
    void addRecent(const string& songName);

    // Displays all songs currently in the recently played tracks list.
    void displayRecent();

    // Returns the name of the most recently played song.
    // Returns a specific string if the list is empty.
    string getLastPlayed();
};

#endif // RECENTPLAYS_H