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

    // then try to insert it at the hashed index
    // if not, run a linear probe until a tombstone or a open index is found
    while(map_[hash_val].first != "__EMPTY__" && 
          map_[hash_val].first != "__TOMBSTONE__"){
            if(map_[hash_val].first == key){
                map_[hash_val].second = val;
                return true;
            }
            hash_val = (hash_val + 1) % capacity_;
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
        map_[idx].first = "__EMPTY__";
        size_--;
        return true;
    }

    return false;
}

int OpenAddressHT::find(const std::string& key){
    int hash_val{hash(key)};
    
    while(map_[hash_val].first != "__EMPTY__"){
        if(map_[hash_val].first == key){
            return hash_val;
        }
        hash_val = (hash_val + 1) % capacity_;
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
        int hash_val{hash(key)};
        while(map_[hash_val].first != "__EMPTY__" || 
              map_[hash_val].first == "__TOMBSTONE__"){
            hash_val = (hash_val + 1) % capacity_;
        }
        new_map[hash_val] = {key, val};  
    }
    map_ = std::move(new_map);
}