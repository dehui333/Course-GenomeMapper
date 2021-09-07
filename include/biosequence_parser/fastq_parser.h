#pragma once

#include <tuple>
#include <vector>

#include "biosequence_parser.h"

class FastqParser : public BiosequenceParser {
    
    private:
        std::vector<std::string> sequences_;
        std::vector<std::string> descriptions_;
        std::vector<std::string> qualities_;
        float average_L_ = 0;
        size_t max_L_ = 0;
        size_t min_L_ = SIZE_MAX;    
          
        
    public:
        void Parse(std::string path);  
        std::string GetSequence(size_t index);
        std::vector<std::string>& GetSequences();
        std::vector<std::string>& GetDescriptions();
        std::string GetDescription(size_t index);
        std::string GetQuality(size_t index);
        size_t NumSequences();
        size_t MaxL();
        size_t MinL();
        float AverageL();
        
        
    
    
    
    
    
    
    
    
    
};
