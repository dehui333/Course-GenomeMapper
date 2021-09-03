#pragma once


#include <vector>
#include <string>
#include <tuple>


namespace mist {
    std::vector<std::tuple<unsigned int, unsigned int, bool>> Minimize(
        const char* sequence, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len);
        
    void Minimizer(
        std::vector<std::string> sequences, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len);
    
    
    
    
    
    
    
    
    
}