#pragma once

#include <utility>
#include <vector>


class FastaParser {
    
    private:
        std::vector<std::pair<std::string, std::string>> sequences;
        int index = 1;
        
          
        
    public:
        float average_L = 0;
        size_t max_L = 0;
        size_t min_L = SIZE_MAX;
    
        void parse(std::string path);  
        std::pair<std::string, std::string> get_sequence(int index);
        size_t num_sequences();
        
        
    
    
    
    
    
    
    
    
    
};
