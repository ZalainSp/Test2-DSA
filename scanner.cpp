#include "scanner.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

Scanner::Scanner(int size) : tableSize(size) {
    table.resize(tableSize);
}

int Scanner::foldHash(int key) const {

    key = abs(key); //handle negative numbers
    string keyStr = to_string(key);
    int sum = 0;
    const int chunkSize = 3; //process 2 digits at a time

    //dispaly folding steps
    cout << "Folding steps for key " << key << ":\n ";
    cout<< "Digits: "<<keyStr<<"\n";
    cout<< "Breaking into 2 digit chunks:\n";

    for(size_t i = 0; i<keyStr.length(); i+=chunkSize) {
        int end = min(i + chunkSize, keyStr.length()); //ensure we dont go out of bounds
        string chunk = keyStr.substr(i, end - i); //extract chunk
        int chunkValue = stoi(chunk);//convert chunk to a integer
        sum += chunkValue; //add chunk value to sum
        cout<<"Chunk:"<<chunk<<"("<<chunkValue<<")\n";
    }
   cout<<"sum of chunks: "<<sum<<"\n";
   //final hash value
    int hashValue = sum % tableSize;
    cout<< "Hash value: "<<sum<<" % "<<tableSize<<" = "<<hashValue<<"\n";
    return hashValue; //return the final hash index
}

int Scanner::doubleHash(int key) const {
 
    return;
}

void Scanner::processKey(int key, const std::string& value) {
   
}

void Scanner::displayTable() const {
   
}

void Scanner::traceKey(int key) const {
   
}

void Scanner::displayFoldingSteps(int key) const {
   
}