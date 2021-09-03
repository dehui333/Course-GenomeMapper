#include "minimizer.h"


namespace mist {
   
    
    

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