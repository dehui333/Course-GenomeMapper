#pragma once


#include <vector>
#include <string>
#include <tuple>
#include <unordered_map>

namespace mist {
    std::vector<std::tuple<unsigned int, unsigned int, bool>> Minimize(
        const char* sequence, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len);
        
    void Minimize(
        std::vector<std::string> sequences, 
        unsigned int kmer_len,
        unsigned int window_len);
    
    unsigned int KmerHash(const char* sequence, unsigned int kmer_len, unsigned int start, bool is_original);
    void Map(const char* sequence, unsigned int sequence_len);
    
    std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>> hash_map;
    std::unordered_map<unsigned int, unsigned int> hash_count;
    unsigned int total_count = 0;
    
    
    
    
    
    
}