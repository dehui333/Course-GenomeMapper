#include <fstream>
#include <iostream>

#include "fastq_parser.h"

void FastqParser::Parse(std::string path) {
    
    std::ifstream input_file(path);
    std::string read_buffer;
    std::string store_buffer_name;
    std::string store_buffer_sequence;
    std::string store_buffer_quality;
    int phase = 0;
    while (getline(input_file, read_buffer)) {
        switch (phase) {
            case 0:
                store_buffer_name = read_buffer.substr(1);
                phase++;
                break;
            case 1:
                store_buffer_sequence = read_buffer;
                phase++;
                break;
            case 2:
                phase++;
                break;
            case 3:
                store_buffer_quality = read_buffer;
                sequences_.push_back(store_buffer_sequence);
                descriptions_.push_back(store_buffer_name);
                qualities_.push_back(store_buffer_quality);
                average_L_ += (store_buffer_sequence.size() - average_L_) / sequences_.size();
                if (store_buffer_sequence.size() > max_L_) {
                    max_L_ = store_buffer_sequence.size();
                } 
                if (store_buffer_sequence.size() < min_L_) {
                    min_L_ = store_buffer_sequence.size();    
                }
                phase = 0;
                break;
            default:
                std::cerr << "Error in parsing!\n";
                return;
            
            
        }
        
    }

    

}
    

std::string FastqParser::GetSequence(size_t i) {
    return sequences_[i];
}

std::string FastqParser::GetDescription(size_t i) {
    return descriptions_[i];
}

std::string FastqParser::GetQuality(size_t i) {
    return qualities_[i];
}

size_t FastqParser::NumSequences() {
    return sequences_.size();
}

size_t FastqParser::MaxL() {
    return max_L_;
}

size_t FastqParser::MinL() {
    return min_L_;
}

float FastqParser::AverageL() {
    return average_L_;
}
