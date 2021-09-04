#include "minimizer.h"

#include <set>

namespace mist {
    //A - 00 C - 01 G - 10 T - 11
    unsigned int kmer_hash(const char* sequence, unsigned int kmer_len, unsigned int start, bool is_original) {
        unsigned int hash = 0;
        unsigned int end = start + kmer_len - 1;
        if (!is_original) {
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
        
        
        std::set<std::tuple<unsigned int, unsigned int, bool>> minimizers_set;
        
        for (unsigned int window_start = 0; window_start <= sequence_len - window_len; window_start++) {
            unsigned int window_min = UINT32_MAX;
            std::set<std::tuple<unsigned int, unsigned int, bool>> minimizers_in_window;
            unsigned int window_end = window_start + window_len - 1;
            for (unsigned int kmer_start = window_start; kmer_start <= window_end - kmer_len + 1; kmer_start++) {
                unsigned int original_value = kmer_hash(sequence, kmer_len, kmer_start, true);
                unsigned int reverse_complement_value = kmer_hash(sequence, kmer_len, kmer_start, false);
                if (original_value != reverse_complement_value) {
                    unsigned int smaller = original_value < reverse_complement_value ? original_value : reverse_complement_value;
                    bool is_original = original_value < reverse_complement_value ? true : false;
                    if (smaller < window_min) {
                        window_min = smaller;
                        minimizers_in_window.clear();
                        minimizers_in_window.insert(std::make_tuple(smaller, kmer_start, is_original));
                    } else if (smaller == window_min) {
                        minimizers_in_window.insert(std::make_tuple(smaller, kmer_start, is_original));
                    }                        
                } 
            }
            minimizers_set.insert(minimizers_in_window.begin(), minimizers_in_window.end());
            
            
            
        }
        std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers(minimizers_set.begin(), minimizers_set.end());
        return minimizers;    
          
    }
    
    void Minimize(
        std::vector<std::string> sequences, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len) {
            
            
            
    };
        
    
    
    
    
    
    
}