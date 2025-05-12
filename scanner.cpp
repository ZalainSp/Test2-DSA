#include "scanner.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

Scanner::Scanner(int size) : tableSize(size) {
    table.resize(tableSize);
}
//first hash function for folding method
int Scanner::foldHash(int key) const {

    int key = abs(key); //handle negative numbers
    string keyStr = to_string(key);
    int sum = 0;
    const int chunkSize = 3; //process 3 digits at a time

    //dispaly folding steps
    cout << "Folding steps for key " << key << ":\n ";
    cout<< "Digits: "<<keyStr<<"\n";
    cout<< "Breaking into 3 digit chunks:\n";

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
//second hash function for double hashing
int Scanner::doubleHash(int key) const {
    int hashValue2 = 7 - (key % 7); //using smaller prime number than table size
    cout<<"Double hash step: 7 - ("<<abs(key)<<" %7) = "<<hashValue2<<"\n"; //output double hash calculation for tracing

    return hashValue2; //return the result
}

void Scanner::processKey(int key, const std::string& value) {
   cout<<"\nProcessing key: "<<key<<" with value: "<<value<<"\n";

    int index = foldHash(key); //get the index using folding method
    int step = doubleHash(key); //get the step using double hashing
    int attempts = 6; //initialize attempts
    int originalIndex = index; //store original index for tracing

    while(attempts < tableSize){
        if(!table[index].occupied){
            table[index].key = key; //insert key
            table[index].value = value; //insert value
            table[index].occupied = true; //mark as occupied
            cout<<"Inserted at index: "<<index<<"\n";
            return; //exit after successful insertion
        }else{
            cout<<"collision at index: "<<index<<" it is occupied by key: "<<table[index].key<<"\n";
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
        if(table[currentIndex].occupied){
            if(table[currentIndex].key == key){
                cout<<"key found at index: "<<table[currentIndex].value<<"\n";
                found = true; //set found flag
                break; //exit loop if key is found
            }else{
                cout<<"slot is occupied by key: "<<table[currentIndex].key<<"\n";
            }
        }else{
            cout<<"slot is empty, the key is not in the table\n";
            found = true; //set found to prevent not found message
            break; //exit loop if empty slot is found
        }
        currentIndex = (currentIndex + hash2) % tableSize; //calculate new index using double hashing
    }
if(!found){
    cout<<"key not found in the table\n"; //output if key is not found
   
}
}
