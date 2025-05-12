#include <iostream>
#include "scanner.h" 

int main() {
    //create a scanner object with a table size of 11
    Scanner myScanner(11);


    //process some key value pairs
    myScanner.processKey(12345, "Jamil");
    myScanner.processKey(67890, "Jeronimo");
    myScanner.processKey(123, "Jayden");//possible collision with 12345 
    myScanner.processKey(456, "Edwin");
    myScanner.processKey(54321, "Jadan"); 
    myScanner.processKey(12345, "Jair"); //trying to insert a key that already exists

    //display the hash table contents
    myScanner.displayTable();

    //trace kets
    myScanner.traceKey(12345);// Key exists
    myScanner.traceKey(67890);//key that exists
    myScanner.traceKey(123);//key exists (cause a collision)
    myScanner.traceKey(99999);//key doesnt exist
    myScanner.traceKey(456);//key exists
    myScanner.traceKey(5000);//key that does not exist

    cout << "\ntesting complete";

    return 0;
}