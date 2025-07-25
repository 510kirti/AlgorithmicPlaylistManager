#include <iostream>
#include <string>
#include <limits>
#include "Playlist.h"    // Include the Playlist class definition
#include "RecentPlays.h" // Include the RecentPlays class definition

using namespace std; // Using directive for the std namespace

// Function to clear the console screen.
// Uses platform-specific commands for Windows and Unix-like systems.
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

int main()
{
    // Create instances of the Playlist and RecentPlays classes.
    // These objects will manage the songs and their history.
    Playlist myPlaylist;

    RecentPlays recentPlays;

    // Display a welcome message and instructions to the user.
    cout << "\t\t\t\a\a\a\a**WELCOME**" << endl;
    cout << "\n**Please use '_' for spaces in song names (e.g., 'My_Favorite_Song')." << endl;

    // Attempt to load the playlist from the default file when the program starts.
    // This ensures that previous sessions' data is loaded.
    myPlaylist.loadFromFile("playlist.txt");

    int choice;      // Variable to store the user's menu choice
    string songName; // Variable to store song names entered by the user

    // Main program loop: continues until the user chooses to exit (choice 10).
    do
    {
        cout << "\n------------------------------------------------\n";
        cout << "1. Add New Song\n";
        cout << "2. Delete Song\n";
        cout << "3. Display Playlist\n";
        cout << "4. Total Songs\n";
        cout << "5. Search Song\n";
        cout << "6. Play Song\n";
        cout << "7. Recently Played List\n";
        cout << "8. Last Played\n";
        cout << "9. Sort Playlist\n";
        cout << "10. Exit\n";
        cout << "------------------------------------------------\n";
        cout << "\a\a\a\aEnter your choice- ";
        cin >> choice;

        // Check if the input failed (e.g., user entered text instead of number).
        if (cin.fail())
        {
            cin.clear(); // Clear the error flags
            // Ignore remaining characters in the input buffer up to a newline or 10000 characters.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; // Set choice to 0 to trigger the default case in switch.
        }

        // Use a switch statement to perform actions based on the user's choice.
        switch (choice)
        {
        case 1: // Add New Song
            cout << "\n\a\a\a\aEnter Song name- ";
            cin >> songName; // Read song name (stops at whitespace)
            myPlaylist.addSong(songName);
            break;
        case 2: // Delete Song
            cout << "\n\a\a\a\aEnter Song name to delete- ";
            cin >> songName; // Read song name to delete
            myPlaylist.deleteSong(songName);
            break;
        case 3: // Display Playlist
            myPlaylist.displayPlaylist();
            break;
        case 4: // Total Songs
            cout << "\nTotal songs: " << myPlaylist.getSongCount() << "\n";
            break;
        case 5:
        { // Search Song (block added for local variable 'found')
            cout << "\n\a\a\a\aEnter song to search- ";
            cin >> songName; // Read song name to search

            if (myPlaylist.getSongCount() > 0)
            {
                // Use the dedicated search method from Playlist class
                bool found = myPlaylist.searchSong(songName);

                if (found)
                {
                    cout << "\n\a\a\a\a#Song Found!\n";
                }
                else
                {
                    cout << "\n\a\a\a\a#Song Not found.\n";
                }
            }
            else
            {
                cout << "\nPlaylist is empty.\n";
            }
            break;
        }
        case 6: // Play Song
            cout << "\n\a\a\a\aEnter song you wish to play- ";
            cin >> songName;                            // Read song name to play
            myPlaylist.playSong(songName, recentPlays); // Call Playlist's playSong method
            break;
        case 7:                          // Recently Played List
            recentPlays.displayRecent(); // Call RecentPlays' displayRecent method
            break;
        case 8:                          // Last Played
            recentPlays.getLastPlayed(); // Call RecentPlays' getLastPlayed method
            break;
        case 9:                              // Sort Playlist
            myPlaylist.sortAlphabetically(); // Call Playlist's sortAlphabetically method
            break;
        case 10:                                   // Exit
            myPlaylist.saveToFile("playlist.txt"); // Save the current playlist state before exiting
            cout << "\nExiting... Playlist saved.\n";
            break;
        default: // Invalid choice
            cout << "\nInvalid choice. Please try again.\n";
            break;
        }
    // Optional:
    //     clearScreen(); // Uncomment to clear screen after each action
    } while (choice != 10); // Loop continues until user chooses to exit

    return 0;
}
