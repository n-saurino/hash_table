#include "HashTable.hpp"

HashTable::HashTable(): capacity_{100}, size_{0} {
   map_.resize(capacity_, {});
}

HashTable::~HashTable(){
    
}

double HashTable::LoadFactor(){
    return static_cast<double>(size_) / capacity_;
}

void HashTable::Rehash(std::vector<std::vector
                       <std::pair<std::string,int>>>& new_map){
    for(auto& bucket : map_){
        for(auto& kv_pair : bucket){
            long new_hash{Hash(kv_pair.first)};
            new_map[new_hash].push_back({kv_pair.first, kv_pair.second});
        } 
    }
    // move the new map into the old map now with updated capacity
    map_ = std::move(new_map);
}

// Print the hash table (for debugging)
void HashTable::Print() const {
    for (size_t i = 0; i < capacity_; ++i) {
        std::cout << "Bucket " << i << ": ";
        for (const auto& [key, value] : map_[i]) {
            std::cout << "[" << key << ": " << value << "] ";
        }
        std::cout << "\n";
    }
}

void HashTable::ResizeAndRehash(){
    capacity_ *= 2;
    std::vector<std::vector<std::pair<std::string,int>>> new_map(capacity_);
    Rehash(new_map);
}

long HashTable::Hash(const std::string& key){
    // pulled a hashing function from the internet
	long hashVal = 0;
    for(auto c : key){
		hashVal = (hashVal << 4) + c;
		long g = hashVal & 0xF0000000L;
		if (g != 0) hashVal ^= g >> 24;
		hashVal &= ~g;
	}
	return hashVal % capacity_;
}

void HashTable::insert(const std::string& key, int value){
    // get hash value of key
    long hash_val{Hash(key)};
    
    // search for duplicate key to replace
    auto idx{find(key)};
    if(idx != map_[hash_val].end()){
        idx->second = value;        
        return;
    }
    
    // duplicate key does not exist so we need to push back a new K,V pair in 
    // the bucket
    map_[hash_val].push_back({key, value});
    
    // need to handle resizing here if load factor reaches .75
    // load factor = # elements / # buckets
    size_++;
    
    if(LoadFactor() > .75){
        ResizeAndRehash();
    }
}

auto HashTable::find(const std::string& key) -> std::vector<
                                               std::pair<std::string,int>>
                                               ::iterator{
    // get hash value of key
    long hash_val{Hash(key)};

    for(auto it = map_[hash_val].begin(); it != map_[hash_val].end(); ++it){
        // will this make a copy of the pair instead of modifying the reference?
         
        if(key == it->first){
            return it;
        }
    }

   return map_[hash_val].end(); 
}

void HashTable::erase(const std::string& key){
   long hash_val = Hash(key);

    std::cout << "Erasing key: " << key << " from bucket " << hash_val << "\n";
    std::cout << "Bucket contents before erase: ";
    for (const auto& pair : map_[hash_val]) {
        std::cout << "[" << pair.first << ": " << pair.second << "] ";
    }
    std::cout << "\n";

    auto idx = find(key);
    if (idx == map_[hash_val].end()) {
        std::cout << "Key not found in bucket.\n";
        return;
    }

    map_[hash_val].erase(idx);
    --size_;

    std::cout << "Bucket contents after erase: ";
    for (const auto& pair : map_[hash_val]) {
        std::cout << "[" << pair.first << ": " << pair.second << "] ";
    }
    std::cout << "\n"; 
}