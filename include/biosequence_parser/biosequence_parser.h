#pragma once

class BiosequenceParser {
       
    public:
        virtual void Parse(std::string path) = 0;  
        virtual std::string GetSequence(size_t index) = 0;
        virtual std::string GetDescription(size_t index) = 0;
        virtual size_t NumSequences() = 0;
        
        
    
    
    
    
    
    
    
    
    
};
