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
                std::pair<std::string, std::string> p (store_buffer_name, store_buffer_sequence);
                sequences_.push_back(p);
                store_buffer_sequence = "";
                average_L_ += (p.second.size() - average_L_) / sequences_.size();
                if (p.second.size() > max_L_) {
                    max_L_ = p.second.size();
                } 
                if (p.second.size() < min_L_) {
                    min_L_ = p.second.size();    
                }
            }
            store_buffer_name = read_buffer.substr(1);
                            
        } else {
            store_buffer_sequence += read_buffer;
        }            
        
    }
    if (store_buffer_sequence != "") {
                std::pair<std::string, std::string> p (store_buffer_name, store_buffer_sequence);
                sequences_.push_back(p);
                average_L_ += (p.second.size() - average_L_) / sequences_.size();
                if (p.second.size() > max_L_) {
                    max_L_ = p.second.size();
                } 
                if (p.second.size() < min_L_) {
                    min_L_ = p.second.size();    
                }
    }
    

}
    

std::string FastaParser::GetSequence(size_t i) {
    return sequences_[i].second;
}

std::string FastaParser::GetDescription(size_t i) {
    return sequences_[i].first;
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