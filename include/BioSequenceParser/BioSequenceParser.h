#pragma once

class BioSequenceParser {
       
    public:
        virtual void parse(std::string path) = 0;  
        virtual std::string get_sequence(size_t index) = 0;
        virtual std::string get_description(size_t index) = 0;
        virtual size_t num_sequences() = 0;
        
        
    
    
    
    
    
    
    
    
    
};
