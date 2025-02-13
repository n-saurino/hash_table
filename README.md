# Implement a Hash Table

## Problem Description

Implement a hash table data structure from scratch that supports basic operations while handling collisions and dynamic resizing. The implementation should use open addressing for collision resolution and maintain an efficient load factor.

## Required Interface

```cpp
class HashTable {
public:
    // Insert a key-value pair into the hash table
    void insert(const std::string& key, int value);
    
    // Return true if the key exists, otherwise false
    bool find(const std::string& key);
    
    // Remove the key-value pair if it exists
    void erase(const std::string& key);
};
```

## Technical Requirements

### Core Functionality
1. Key-value storage and retrieval
2. Efficient lookup operations
3. Dynamic memory management
4. Proper collision handling

### Specific Constraints
1. Use open addressing for collision resolution
2. Implement dynamic resizing when load factor > 0.75
3. Handle string keys and integer values
4. Maintain O(1) average time complexity for operations

## Implementation Guidelines

### Key Components

1. Hash Function
   - Efficient string hashing algorithm
   - Good distribution of hash values
   - Minimal collisions

2. Collision Resolution
   - Open addressing implementation
   - Probing sequence definition
   - Handling of deleted entries

3. Dynamic Resizing
   - Load factor monitoring
   - Rehashing implementation
   - Memory management

## Example Usage

```cpp
HashTable table;

// Insert elements
table.insert("apple", 5);
table.insert("banana", 8);
table.insert("orange", 3);

// Look up elements
assert(table.find("apple") == true);
assert(table.find("grape") == false);

// Remove elements
table.erase("banana");
assert(table.find("banana") == false);
```

## Performance Considerations

### Time Complexity
- Average case: O(1) for all operations
- Worst case: O(n) when many collisions occur

### Space Complexity
- O(n) where n is the number of stored elements
- Additional overhead for load factor management

## Best Practices

1. Choose appropriate initial size
2. Implement efficient probing sequence
3. Handle edge cases properly
4. Consider thread safety if needed
5. Implement proper error handling

## Testing Strategies

### Test Cases
1. Basic operations
   - Insert new elements
   - Find existing elements
   - Erase elements
   - Find non-existent elements

2. Edge Cases
   - Empty table operations
   - Duplicate keys
   - Deleted key handling
   - Table resizing scenarios

3. Performance Tests
   - High load factor behavior
   - Collision handling efficiency
   - Resizing performance
   - Memory usage patterns

## Common Pitfalls to Avoid

1. Poor hash function distribution
2. Inefficient collision resolution
3. Memory leaks during resizing
4. Incorrect load factor calculation
5. Improper handling of deleted entries

## Follow-up Considerations

1. How would you make the implementation thread-safe?
2. Can you optimize the hash function for better distribution?
3. How would you handle different value types?
4. What strategies could improve cache efficiency?
5. How would you implement iteration over the hash table?
