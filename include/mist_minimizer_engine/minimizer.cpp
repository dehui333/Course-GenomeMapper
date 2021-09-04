#include "minimizer.h"

#include <set>

namespace mist {
    //A - 00 C - 01 G - 10 T - 11
    unsigned int KmerHash(const char* sequence, unsigned int kmer_len, unsigned int start, bool is_original) {
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
            //std::cout << window_start << "\n";
            unsigned int window_min = UINT32_MAX;
            std::set<std::tuple<unsigned int, unsigned int, bool>> minimizers_in_window;
            unsigned int window_end = window_start + window_len - 1;
            for (unsigned int kmer_start = window_start; kmer_start <= window_end - kmer_len + 1; kmer_start++) {
                unsigned int original_value = KmerHash(sequence, kmer_len, kmer_start, true);
                unsigned int reverse_complement_value = KmerHash(sequence, kmer_len, kmer_start, false);
                //std::cout <<"original " << original_value << "\n";
                //std::cout <<"complement " << reverse_complement_value << "\n";
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
        unsigned int kmer_len,
        unsigned int window_len) {
        for (unsigned int i = 0; i < sequences.size(); i++) {
            auto m = Minimize(sequences[i].c_str(), sequences[i].size(), kmer_len, window_len);
            for (auto t: m) {
                unsigned int hash_value = std::get<0>(t);
                if (mist::hash_map.find(hash_value) == mist::hash_map.end()) {
                    std::vector<std::tuple<unsigned int, unsigned int, bool>> v;
                    v.push_back(std::make_tuple(i, std::get<1>(t), std::get<2>(t)));
                    mist::hash_map[hash_value] = v;
                } else {
                    mist::hash_map[hash_value].push_back(std::make_tuple(i, std::get<1>(t), std::get<2>(t)));
                }
                if (mist::hash_count.find(hash_value) == mist::hash_count.end()) {
                    mist::hash_count[hash_value] = 1;
                    total_count++;
                } else {
                    mist::hash_count[hash_value]++;
                    total_count++;
                }
                
            }
            
        }       
    }
}
/*
int main(int argc, char** argv) {
    std::vector<std::tuple<unsigned int, unsigned int, bool>> m = mist::Minimize("ATCGATCGAT", 10, 3, 5);
    for (auto p: m) {
        std::cout << std::get<0>(p) << "\n";
        std::cout << std::get<1>(p) << "\n";
        std::cout << std::get<2>(p) << "\n\n";
    }
}*/