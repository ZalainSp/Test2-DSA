#This project implements a hash table using the Folding Method as the primary hash function and Double Hashing for collision resolution. It stores integer keys paired with string values 
(e.g., student IDs and names), and supports operations like insertion, tracing, and visualization of the table.

##Features:
- Folding Hashing (Breaks key into 3 digit chunks and sums them)
- Double Hashing for collision resolution
- Tracing of key placement with detailed step by step output
- Displays full table with all keys and values

##File Structure:
main.cpp - Demonstrates how to use the Scanner class by inserting, tracing, and displaying keys.
hash.h - Header file that declares the Scanner class and HashEntry structure.
hash.cpp - Implements all hash functions, insertion logic, tracing, and display functionality.

##Primary Hash Function - Folding Method
The foldHash(int key) method:
- Breaks the key into 3 digit chunks
- Converts each chunk to an integer
- Sums all chunks
- Applies modulo with table size to get the index

##Secondary Hash Function - Double Hashing
The doubleHash(int key) method:
- Uses: step = 7 - (key % 7)
- Ensures non-zero step for probing

##Insertion: processKey(int key, const string& value)
- Applies folding hash for initial index
- Uses double hashing to resolve collisions

##Tracing: traceKey(int key)
- Walks through probing steps to find the key
- Displays where the key is found or if it's not present

##Display: displayTable()
- Shows each index, the key stored, and the value (or if it’s empty)

##How to run:
g++ main.cpp hash.cpp -o program
./program


https://youtu.be/mLUxSR2gfqw
