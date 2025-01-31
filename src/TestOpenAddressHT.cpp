#include <gtest/gtest.h>
#include "OpenAddressHT.hpp"

class OpenAddressHTTest : public ::testing::Test {
protected:
    OpenAddressHT ht{};
};

// **Test Case 1: Insert and Find**
TEST_F(OpenAddressHTTest, InsertAndFind) {
    EXPECT_EQ(ht.insert("apple", 10), true);
    EXPECT_EQ(ht.insert("banana", 20), true);
    EXPECT_EQ(ht.insert("cherry", 30), true);

    int appleIdx = ht.find("apple");
    int bananaIdx = ht.find("banana");
    int cherryIdx = ht.find("cherry");

    // Ensure the keys are found somewhere in the table
    EXPECT_NE(appleIdx, -1);
    EXPECT_NE(bananaIdx, -1);
    EXPECT_NE(cherryIdx, -1);

    // Ensure "grape" is not found
    EXPECT_EQ(ht.find("grape"), -1);
}

// **Test Case 2: Insert Duplicate Key (Update Value)**
TEST_F(OpenAddressHTTest, InsertDuplicateKey) {
    EXPECT_EQ(ht.insert("apple", 10), true);
    EXPECT_EQ(ht.insert("apple", 50), true); // Overwrites existing value

    int idx = ht.find("apple");
    EXPECT_NE(idx, -1);
    EXPECT_EQ(ht.map_[idx].second, 50);
}

// **Test Case 3: Erase Key and Ensure It’s Removed**
TEST_F(OpenAddressHTTest, EraseKey) {
    ht.insert("apple", 10);
    ht.insert("banana", 20);

    EXPECT_EQ(ht.erase("apple"), true);
    EXPECT_EQ(ht.find("apple"), -1); // Should not be found
    EXPECT_NE(ht.find("banana"), -1); // Banana should still exist
}

// **Test Case 4: Erase Non-Existent Key**
TEST_F(OpenAddressHTTest, EraseNonExistentKey) {
    ht.insert("apple", 10);
    EXPECT_EQ(ht.erase("banana"), false); // Not in table
    EXPECT_NE(ht.find("apple"), -1); // Ensure existing key is not affected
}

// **Test Case 5: Handle Collisions with Open Addressing**
TEST_F(OpenAddressHTTest, HandleCollisions) {
    // Reduce capacity to force collisions
    ht.capacity_ = 5; 

    EXPECT_EQ(ht.insert("apple", 10), true);
    EXPECT_EQ(ht.insert("banana", 20), true);
    EXPECT_EQ(ht.insert("cherry", 30), true);

    EXPECT_NE(ht.find("apple"), -1);
    EXPECT_NE(ht.find("banana"), -1);
    EXPECT_NE(ht.find("cherry"), -1);
}

// **Test Case 6: Load Factor and Resizing**
TEST_F(OpenAddressHTTest, LoadFactorAndResize) {
    int initial_capacity = ht.capacity_;

    // Insert elements until resizing is triggered
    for (int i = 0; i < initial_capacity * Constants::LOAD_FACTOR + 1; ++i) {
        EXPECT_EQ(ht.insert("key" + std::to_string(i), i), true);
    }

    EXPECT_GT(ht.capacity_, initial_capacity); // Ensure resizing occurred
}

// **Test Case 7: Ensure Correct Load Factor Calculation**
TEST_F(OpenAddressHTTest, LoadFactorComputation) {
    EXPECT_DOUBLE_EQ(ht.loadfactor(), 0.0);

    ht.insert("apple", 10);
    EXPECT_DOUBLE_EQ(ht.loadfactor(), 1.0 / ht.capacity_);

    ht.insert("banana", 20);
    EXPECT_DOUBLE_EQ(ht.loadfactor(), 2.0 / ht.capacity_);
}

// **Test Case 8: Rehashing Maintains Data Integrity**
TEST_F(OpenAddressHTTest, RehashMaintainsData) {
    int initial_capacity = ht.capacity_;

    // Insert elements to trigger resizing
    for (int i = 0; i < initial_capacity; ++i) {
        EXPECT_EQ(ht.insert("key" + std::to_string(i), i), true);
    }

    for (int i = 0; i < initial_capacity; ++i) {
        EXPECT_NE(ht.find("key" + std::to_string(i)), -1);
    }
}

// **Test Case 9: Tombstone Handling in Erase**
TEST_F(OpenAddressHTTest, TombstoneHandling) {
    EXPECT_EQ(ht.insert("apple", 10), true);
    EXPECT_EQ(ht.insert("banana", 20), true);
    EXPECT_EQ(ht.erase("apple"), true); // Mark as tombstone

    // Insert a new key that reuses the tombstone slot
    EXPECT_EQ(ht.insert("grape", 30), true);

    EXPECT_NE(ht.find("grape"), -1);
    EXPECT_EQ(ht.find("apple"), -1); // Apple should remain deleted
}

// **Test Case 10: Insert After Deletions**
TEST_F(OpenAddressHTTest, InsertAfterErase) {
    EXPECT_EQ(ht.insert("apple", 10), true);
    EXPECT_EQ(ht.erase("apple"), true);

    // Insert a new key after deletion (tombstone reuse)
    EXPECT_EQ(ht.insert("banana", 20), true);
    EXPECT_NE(ht.find("banana"), -1);
    EXPECT_EQ(ht.find("apple"), -1); // Apple should still be erased
}