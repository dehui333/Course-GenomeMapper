#include "minimizer.h"


namespace mist {
    std::vector<std::tuple<unsigned int, unsigned int, bool>> Minimize(
        const char* sequence, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len) {
        
        std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers;
        for (unsigned int window_start = 0; window_start <= sequence_len - window_len; window_start++) {
            unsigned int window_end = window_start + window_len - 1;
            std::string minimizer = "Z";
            for (unsigned int kmer_start = window_start; window_end - kmer_len + 1; kmer_start++) {
                std::string kmer = "";     
                for (unsigned int i = kmer_start; i < kmer_start + kmer_len; i++) {
                     kmer += sequence[i];
                }
                if (kmer < minimizer) {
                    minimizer = kmer;
                }                    
            }
            
                



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