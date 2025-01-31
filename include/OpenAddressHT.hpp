#pragma once
#include <iostream>
#include <vector>
#include <utility>

namespace Constants{
    const double LOAD_FACTOR{.75};
}

class OpenAddressHT{
public:
    OpenAddressHT();
    ~OpenAddressHT();
    bool insert(const std::string& key, int val);
    bool erase(const std::string& key);
    int find(const std::string& key);
    int hash(const std::string& key);
    double loadfactor() const;
    void resizeandrehash();
    void rehash(std::vector<std::pair<std::string, int>>& new_map);
    
    std::vector<std::pair<std::string, int>> map_; 
    int capacity_{4};
    int size_{0}; 

private:
    // got lazy for testing
    // std::vector<std::pair<std::string, int>> map_; 
    // int capacity_{100};
    // int size_{0}; 
    
};