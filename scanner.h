#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Scanner {
public:
    //constructor takes table size 
    Scanner(int size = 11);
    
    //scan and process a key using folding method and double hashing
    void processKey(int key, const string& value);
    
    //display the hash table contents
    void displayTable() const;
    
    //trace the hashing steps for a given key
    void traceKey(int key) const;

struct HashEntry {
        int key;
        string value;
        bool occupied;
        HashEntry() : key(0), value(""), occupied(false) {}
    };

    vector<HashEntry> table;
    int tableSize;

    //first hash function- folding method
    int foldHash(int key) const;
    
    //second hash function for double hashing
    int doubleHash(int key) const;
    
    //helper to visualize folding steps
    void displayFoldingSteps(int key) const;
};

#endif 