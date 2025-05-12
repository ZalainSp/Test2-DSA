#include "hash.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

Scanner::Scanner(int size) : tableSize(size) {
    if (tableSize <= 0) {
    cout << "Warning: Table size must be positive. Setting to default size 11." << endl;
    tableSize = 11;
}

    table.resize(tableSize);
}
//first hash function for folding method
int Scanner::foldHash(int key) const {

    int positiveKey = abs(key); //handle negative numbers
    string keyStr = to_string(positiveKey);
    int sum = 0;
    const int chunkSize = 3; //process 3 digits at a time

    //dispaly folding steps
    cout << "Folding steps for key " << positiveKey << ":\n ";
    cout<< "Digits: "<<keyStr<<"\n";
    cout<< "Breaking into 3 digit chunks:\n";

    for(size_t i = 0; i<keyStr.length(); i+=chunkSize) {
        string chunk = keyStr.substr(i, min((size_t)chunkSize, keyStr.length() - i));
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
//second hash function for double hashing
int Scanner::doubleHash(int key) const {
    int positiveKey = abs(key); //handle negative numbers
    int hashValue2 = 7 - (positiveKey % 7); //using smaller prime number than table size
    if(hashValue2 == 0) {
        hashValue2 = 7; //avoid zero step
    }
    cout<<"Double hash step: 7 - ("<<positiveKey<<" %7) = "<<hashValue2<<"\n"; //output double hash calculation for tracing

    return hashValue2; //return the result
}

void Scanner::processKey(int key, const std::string& value) {
   cout<<"\nProcessing key: "<<key<<" with value: "<<value<<"\n";

    int index = foldHash(key); //get the index using folding method
    int step = doubleHash(key); //get the step using double hashing
    cout << "Attempting insertion with initial index " << index << " and step " << step << "." << endl;
    int attempts = 0; //initialize attempts
    int originalIndex = index; //store original index for tracing

    while(attempts < tableSize){
        cout << " Attempt " << (attempts + 1) << ": Trying index " << originalIndex << ". ";
        if(!table[originalIndex].occupied){
            table[originalIndex].key = key; //insert key
            table[originalIndex].value = value; //insert value
            table[originalIndex].occupied = true; //mark as occupied
            cout<<"Inserted at index: "<<index<<"\n";
            return; //exit after successful insertion
        }else{
            if(table[originalIndex].key == key){
                cout<<"slot is occupied by key: "<<table[index].key<<". Key already exists.\n";
                return; //exit if key already exists
            }
            cout << "Collision: Slot occupied by key " << table[originalIndex].key;
        }
        originalIndex = (index + (attempts + 1)* step) % tableSize;
        if(attempts == 0){
            originalIndex = (index + step) % tableSize;
        } else {
            originalIndex = (originalIndex + step) % tableSize;
        }
        originalIndex = (originalIndex + step) % tableSize; //calculate new index using double hashing
        attempts++; //increment attempts
    }
    cout << "Could not insert key " << key << ". the table might be full or no empty slot was found.\n";
}
void Scanner::displayTable() const {
   cout<<"\nHash Table Contents:\n";
   cout<<setw(10)<<"Index"<<setw(10)<<"keys"<<setw(15)<<"Values"<<"\n"; 
   for(int i = 0; i<tableSize; i++){
    if(table[i].occupied){
        cout<<setw(10)<<i<<setw(10)<<table[i].key<<setw(15)<<table[i].value<<"\n"; //display occupied slots using setw for formatting alignment
    }else{
        cout<<setw(10)<<i<<setw(10)<<"empty"<<setw(15)<<"empty"<<"\n"; //display empty slots using setw for formatting alignment
    }
   }
}

void Scanner::traceKey(int key) const {
    cout<<"\nTracing key: "<<key<<"\n";

    int hash1 = foldHash(key); //get the first hash value
    int hash2 = doubleHash(key); //get the second hash value

    cout<<"First hash value: "<<hash1<<"\n"<<"Second hash value: "<<hash2<<"\n";

    int currentIndex = hash1; //initialize current index
    bool found = false; //initialize found flag
    for(int i = 0; i<tableSize; i++){
        if(i>0){
            currentIndex = (hash1 + i * hash2) %tableSize; //calculate for probe i
        }else{
            currentIndex = hash1;
        }
        
        cout << " Attempt " << (i + 1) << ": checking index " << currentIndex<<". ";
        if(table[currentIndex].occupied){

            if(table[currentIndex].key == key){
                cout<<"key found at index: "<<table[currentIndex].value<<"\n";
                found = true; //set found flag
                break; //exit loop if key is found
            }else{
                cout<<"slot is occupied by key: "<<table[currentIndex].key<<". \n";
            }
        }else{
            cout<<"slot is empty, the key is not in the table\n";
            return; //exit loop if empty slot is found
        }
        
    }
if(!found){
    cout<<"key not found in the table\n"; //output if key is not found
   
}
}
