#include "minimizer.h"


namespace mist {
    //A - 00 C - 01 G - 10 T - 11
    unsigned int kmer_hash(const char* sequence, unsigned int kmer_len, unsigned int start, bool reverse_complement) {
        unsigned int hash = 0;
        unsigned int end = start + kmer_len - 1;
        if (reverse_complement) {
            for (int i = 0; i < kmer_len; i++) {
                char c = sequence[end - i];
                if (c == 'A') {
                    hash += 3;
                    hash = hash << 2;
                } else if (c == 'C') {
                    hash += 2;
                    hash = hash << 2;
                } else if (c == 'G') {
                    hash += 1;
                    hash = hash << 2;    
                } else {
                    hash = hash << 2;
                }
            }
            
        } else {
            for (int i = 0; i < kmer_len; i++) {
                char c = sequence[start + i];
                if (c == 'A') {
                    hash = hash << 2;
                } else if (c == 'C') {
                    hash += 1;
                    hash = hash << 2;
                } else if (c == 'G') {
                    hash += 2;
                    hash = hash << 2;    
                } else {
                    hash += 3;
                    hash = hash << 2;
                }
            }
            
            
        }
        hash = ~hash + (hash << 15);
        hash = hash ^ (hash >> 12);
        hash = hash + (hash << 2);
        hash = hash ^ (hash >> 4);
        hash = hash * 2057; 
        hash = hash ^ (hash >> 16);
        return hash;
    }
    
    
    

    std::vector<std::tuple<unsigned int, unsigned int, bool>> Minimize(
        const char* sequence, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len) {
        
        std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers;
        for (unsigned int window_start = 0; window_start <= sequence_len - window_len; window_start++) {
            std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers_in_window;
            unsigned int window_end = window_start + window_len - 1;
        }
        return minimizers;    
          
    }
    
    void Minimizer(
        std::vector<std::string> sequences, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len) {
            
            
            
    };
        
    
    
    
    
    
    
}