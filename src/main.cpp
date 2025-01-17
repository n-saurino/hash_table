#include <stdio.h>
// #include "HashTable.hpp"
#include <iostream>
#include <cassert>
#include "OpenAddressHT.hpp"

// Helper function to print a test result
// void print_test_result(const std::string& test_name, bool passed) {
//     std::cout << (passed ? "[PASSED] " : "[FAILED] ") << test_name << std::endl;
// }

// Function to test the hash table implementation
// void test_hash_table() {
//     HashTable ht;

//     // Test 1: Basic insert and find
//     ht.insert("apple", 5);
//     auto it = ht.find("apple");
//     print_test_result("Basic Insert and Find", 
//                       it != ht.map_[ht.hash("apple")].end() && it->second == 5);

//     // Test 2: Insert duplicate key (update value)
//     ht.insert("apple", 10);
//     it = ht.find("apple");
//     print_test_result("Insert Duplicate Key", 
//                       it != ht.map_[ht.hash("apple")].end() 
//                       && it->second == 10);

//     // Test 3: Insert multiple keys and find them
//     ht.insert("banana", 20);
//     ht.insert("cherry", 30);
//     print_test_result("Insert Multiple Keys",
//                       ht.find("banana") != ht.map_[ht.hash("banana")].end() &&
//                       ht.find("cherry") != ht.map_[ht.hash("cherry")].end());

//     // Test 4: Erase a key and ensure it is removed
//     ht.erase("apple");
//     it = ht.find("apple");
//     print_test_result("Erase Key", it == ht.map_[ht.hash("apple")].end());

//     // Test 5: Erase a nonexistent key (no crash, no changes)
//     size_t old_size = ht.map_[ht.hash("banana")].size();
//     ht.erase("nonexistent");
//     print_test_result("Erase Nonexistent Key", 
//                       old_size == ht.map_[ht.hash("banana")].size());

//     // Test 6: Handle collisions (same hash bucket)
//     ht.insert("cat", 40);  // Intentionally create a collision-prone key
//     ht.insert("tac", 50);  // "cat" and "tac" might hash to the same bucket
//     print_test_result("Handle Collisions",
//                       ht.find("cat") != ht.map_[ht.hash("cat")].end() &&
//                       ht.find("tac") != ht.map_[ht.hash("tac")].end());

//     // Test 7: Resizing (load factor management)
//     for (int i = 0; i < 90; ++i) {
//         ht.insert("key" + std::to_string(i), i);
//     }
    
//     // Test if resizing logic is implemented
//     print_test_result("Resizing (Load Factor < 0.75)", true); 
//     ht.print();
// }
void test_insert_single_element() {
    OpenAddressHT ht;
    assert(ht.insert("key1", 1) == true);
    assert(ht.find("key1") != -1);
    std::cout << "test_insert_single_element passed!" << std::endl;
}

void test_insert_multiple_elements() {
    OpenAddressHT ht;
    assert(ht.insert("key1", 1) == true);
    assert(ht.insert("key2", 2) == true);
    assert(ht.insert("key3", 3) == true);
    assert(ht.find("key1") != -1);
    assert(ht.find("key2") != -1);
    assert(ht.find("key3") != -1);
    std::cout << "test_insert_multiple_elements passed!" << std::endl;
}

void test_insert_with_collisions() {
    OpenAddressHT ht;
    assert(ht.insert("key1", 1) == true);
    assert(ht.insert("key1", 2) == false); // Duplicate key
    assert(ht.find("key1") != -1);
    std::cout << "test_insert_with_collisions passed!" << std::endl;
}

void test_insert_trigger_rehash() {
    OpenAddressHT ht;
    for (int i = 0; i < 80; ++i) {
        assert(ht.insert("key" + std::to_string(i), i) == true);
    }
    assert(ht.loadfactor() <= Constants::LOAD_FACTOR);
    std::cout << "test_insert_trigger_rehash passed!" << std::endl;
}


int main() {
    // test_hash_table();
    test_insert_single_element();
    test_insert_multiple_elements();
    test_insert_with_collisions();
    test_insert_trigger_rehash();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}	

