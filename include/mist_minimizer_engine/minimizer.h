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
        unsigned int window_len,
        std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>>& hash_map,
        std::unordered_map<unsigned int, unsigned int>& hash_count,
        unsigned int& total_count    
        );
    
    unsigned int KmerHash(const char* sequence, unsigned int kmer_len, unsigned int start, bool is_original);
    std::vector<std::tuple<unsigned int, bool, unsigned int, unsigned int, unsigned int, unsigned int> > Map(const char* sequence,
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len,
        int cluster_band_size,
        double filter,
        std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>>& hash_map,
        std::unordered_map<unsigned int, unsigned int>& hash_count,
        unsigned int& total_count,
        unsigned int l_limit
        );
    std::tuple<unsigned int, bool, unsigned int, unsigned int, unsigned int, unsigned int> FindOverlap(std::vector<std::tuple<unsigned int, bool, int, unsigned int>> roughly_colinear, unsigned int& increasing_len);
    

    
    
}