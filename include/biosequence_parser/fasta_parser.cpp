#include <fstream>
#include <iostream>

#include "fasta_parser.h"

void FastaParser::Parse(std::string path) {
    std::ifstream input_file(path);
    std::string read_buffer;
    std::string store_buffer_name;
    std::string store_buffer_sequence = "";
    while (getline(input_file, read_buffer)) {
        if (read_buffer[0] == '>') {
         
            if (store_buffer_sequence != "") {
                
                sequences_.push_back(store_buffer_sequence);
                descriptions_.push_back(store_buffer_name);
                average_L_ += (store_buffer_sequence.size() - average_L_) / sequences_.size();
                if (store_buffer_sequence.size() > max_L_) {
                    max_L_ = store_buffer_sequence.size();
                } 
                if (store_buffer_sequence.size() < min_L_) {
                    min_L_ = store_buffer_sequence.size();    
                }
                
                store_buffer_sequence = "";
                
                
            }
            store_buffer_name = read_buffer.substr(1);
                            
        } else {
            store_buffer_sequence += read_buffer;
        }            
        
    }
    if (store_buffer_sequence != "") {
                descriptions_.push_back(store_buffer_name);          
                sequences_.push_back(store_buffer_sequence);
                average_L_ += (store_buffer_sequence.size() - average_L_) / sequences_.size();
                if (store_buffer_sequence.size() > max_L_) {
                    max_L_ = store_buffer_sequence.size();
                } 
                if (store_buffer_sequence.size() < min_L_) {
                    min_L_ = store_buffer_sequence.size();    
                }
    }
    

}
    

std::string FastaParser::GetSequence(size_t i) {
    return sequences_[i];
}

std::string FastaParser::GetDescription(size_t i) {
    return descriptions_[i];
}


size_t FastaParser::NumSequences() {
    return sequences_.size();
}

size_t FastaParser::MaxL() {
    return max_L_;
}

size_t FastaParser::MinL() {
    return min_L_;
}

float FastaParser::AverageL() {
    return average_L_;
}