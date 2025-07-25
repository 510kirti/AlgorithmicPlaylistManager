#ifndef SONGNODE_H
#define SONGNODE_H

#include <string> 
using namespace std;
struct SongNode {
    string songName; 
    SongNode* next;       
    SongNode* prev;       

    // Constructor for SongNode:
    
    SongNode(const string& name){
        songName = name;
        next = nullptr;
        prev = nullptr;
    }
};

#endif 