#pragma once

#include <tuple>
#include <vector>

#include "biosequence_parser.h"

class FastqParser : public BiosequenceParser {
    
    private:
        std::vector<std::tuple<std::string, std::string, std::string>> sequences_;
        float average_L_ = 0;
        size_t max_L_ = 0;
        size_t min_L_ = SIZE_MAX;    
          
        
    public:
        void Parse(std::string path);  
        std::string GetSequence(size_t index);
        std::string GetDescription(size_t index);
        std::string GetQuality(size_t index);
        size_t NumSequences();
        size_t MaxL();
        size_t MinL();
        float AverageL();
        
        
    
    
    
    
    
    
    
    
    
};