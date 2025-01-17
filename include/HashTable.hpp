#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// HashTable Requirements
// void insert(const std::string& key, int value): Insert a key-value pair into 
//   the hash table.
// bool find(const std::string& key): Return true if the key exists, otherwise 
//   false.
// void erase(const std::string& key): Remove the key-value pair if it exists.

// Constraints:
// Handle collisions using separate chaining.
// Resize the hash table dynamically when the load factor exceeds 0.75. 

// Considerations:
// need to figure out the underlying data structure that allows for O(1) find 
// simplest hashing algorithm is modulo by hashtable size
// use a vector of vectors (fast because contiguous in memory)
// the vector that handles chaining will store a pair<string, int>

// every time we insert, we need to iterate through the bucket vector to check
// for a duplicate key and then either overwrite the value or add a new k,v pair

class HashTable{
public:
HashTable();
~HashTable();
void insert(const std::string& key, int value);
auto find(const std::string& key) -> std::vector<std::pair<std::string,int>>
                                     ::iterator;
void erase(const std::string& key);
std::vector<std::vector<std::pair<std::string,int>>> map_;
long hash(const std::string& key);
double LoadFactor();
void ResizeAndRehash();
void Rehash(std::vector<std::vector
            <std::pair<std::string,int>>>& new_map);
void print() const;
int capacity_{};
int size_{};

private:
    
};