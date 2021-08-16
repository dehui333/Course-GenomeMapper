#pragma once

#include <utility>
#include <vector>

/*
FastaParser's constructor takes a path to a FASTA file, parses and stores the sequences internally. 
*/


class FastaParser {
    
    private:
        
        std::vector<std::pair<std::string, std::string>> sequences;
        void parse(std::string path);    
        
    public:
        FastaParser(std::string path);
        std::pair<std::string, std::string> get_sequence(int index);
        int num_sequences();
        
    
    
    
    
    
    
    
    
    
};
