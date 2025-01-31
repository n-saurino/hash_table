#include "OpenAddressHT.hpp"
/* 
JUST REALIZED THE OPENADDRESSHT ISN'T HANDLING TOMBSTONES PROPERLY!!
NEED TO REVISE THIS SOLUTION!
*/

OpenAddressHT::OpenAddressHT(): capacity_{100}, size_{0}, map_(100, 
                                {"__EMPTY__", 0}) {

}

OpenAddressHT::~OpenAddressHT(){

}

bool OpenAddressHT::insert(const std::string& key, int val){
    // hash the key
    int hash_val{hash(key)};
    int original_hash_val{hash_val};
    int tombstone_idx{-1};

    // then try to insert it at the hashed index
    // if not, run a linear probe until a tombstone or a open index is found
    while(map_[hash_val].first != "__EMPTY__"){
        if(map_[hash_val].first == key){
            map_[hash_val].second = val;
            return true;
        }
  
        if(map_[hash_val].first == "__TOMBSTONE__" && tombstone_idx == -1){
            tombstone_idx = hash_val;
        }

        hash_val = (hash_val + 1) % capacity_;
        
        if(hash_val == original_hash_val) break;
    }

    if(tombstone_idx > -1){
       hash_val = tombstone_idx; 
    }

    map_[hash_val] = {key, val};
    size_++;
    
    // handle rehash if load factor > .75
    if(loadfactor() > Constants::LOAD_FACTOR){
        // RESIZE and REHASH
        resizeandrehash();
    }
    return true;
}

bool OpenAddressHT::erase(const std::string& key){
    int idx{find(key)};
    if(idx != -1){
        map_[idx].first = "__TOMBSTONE__";
        size_--;
        return true;
    }

    return false;
}

int OpenAddressHT::find(const std::string& key){
    int hash_val{hash(key)};
    
    // need to keep track of the original hash value so we can confirm
    // we did a full loop through the map_
    int original_hash = hash_val;
    
    while(map_[hash_val].first != "__EMPTY__"){
        if(map_[hash_val].first == key){
            return hash_val;
        }
        hash_val = (hash_val + 1) % capacity_;

        // break condition in case we end up looping through a full hash_table
        if(hash_val == original_hash) break;
    }

    return -1;    
}

int OpenAddressHT::hash(const std::string& key){
    int p{31};
    int hash_val{0};
    long long p_pow{1};
    for(auto c : key){
       hash_val = (hash_val + (c - '0' + 1) * p_pow) % capacity_;
       p_pow = (p_pow * p) % capacity_; 
    } 
    return hash_val;
}

double OpenAddressHT::loadfactor() const{
    return static_cast<double>(size_)/capacity_;
}

void OpenAddressHT::resizeandrehash(){
    capacity_ *= 2;
    std::vector<std::pair<std::string, int>> new_map(capacity_, 
                                                     {"__EMPTY__", 0});
    rehash(new_map);
}

void OpenAddressHT::rehash(std::vector<std::pair<std::string, int>>& new_map){

    for(const auto& [key, val] : map_){
        // don't want to hash a delimiter string
        if(key != "__EMPTY__" && key != "__TOMBSTONE__"){
            int hash_val{hash(key)};
            while(map_[hash_val].first != "__EMPTY__"){
                hash_val = (hash_val + 1) % capacity_;
            }
            new_map[hash_val] = {key, val};
        }
        map_ = std::move(new_map);
    }
}