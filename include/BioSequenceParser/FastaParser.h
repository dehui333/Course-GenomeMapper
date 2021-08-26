#pragma once

#include <utility>
#include <vector>

#include "BioSequenceParser.h"

class FastaParser : public BioSequenceParser {
    
    private:
        std::vector<std::pair<std::string, std::string>> sequences;
        int index = 1;
        
          
        
    public:
        float average_L = 0;
        size_t max_L = 0;
        size_t min_L = SIZE_MAX;
    
        void parse(std::string path);  
        std::string get_sequence(size_t index);
        std::string get_description(size_t index);
        size_t num_sequences();
        
        
    
    
    
    
    
    
    
    
    
};
