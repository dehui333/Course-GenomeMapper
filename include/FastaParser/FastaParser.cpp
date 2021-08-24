#include <fstream>
#include <iostream>

#include <utility>
#include <vector>

#include "FastaParser.h"


void FastaParser::parse(std::string path) {
    std::ifstream input_file(path);
    std::string read_buffer;
    std::string store_buffer_name;
    std::string store_buffer_sequence = "";
    int index = 1;
    while (getline(input_file, read_buffer)) {
        if (read_buffer[0] == '>') {
            store_buffer_name = read_buffer.substr(1);
            if (store_buffer_sequence != "") {
                std::pair<std::string, std::string> p (store_buffer_name, store_buffer_sequence);
                sequences.push_back(p);
                average_L += (p.second.size() - average_L) / index++;
                if (p.second.size() > max_L) {
                    max_L = p.second.size();
                } 
                if (p.second.size() < min_L) {
                    min_L = p.second.size();    
                }
            }                
        } else {
            store_buffer_sequence += read_buffer;
        }            
        
    }
    if (store_buffer_sequence != "") {
                std::pair<std::string, std::string> p (store_buffer_name, store_buffer_sequence);
                sequences.push_back(p);
                average_L += (p.second.size() - average_L) / index;
                if (p.second.size() > max_L) {
                    max_L = p.second.size();
                } 
                if (p.second.size() < min_L) {
                    min_L = p.second.size();    
                }
    }

}
    
FastaParser::FastaParser(std::string path) {
    parse(path);
}

std::pair<std::string, std::string> FastaParser::get_sequence(int index) {
    return sequences[index];
}

int FastaParser::num_sequences() {
    return sequences.size();
}







    
