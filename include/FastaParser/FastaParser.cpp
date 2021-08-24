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
         
            if (store_buffer_sequence != "") {
                std::pair<std::string, std::string> p (store_buffer_name, store_buffer_sequence);
                sequences.push_back(p);
                store_buffer_sequence = "";
                average_L += (p.second.size() - average_L) / index++;
                if (p.second.size() > max_L) {
                    max_L = p.second.size();
                } 
                if (p.second.size() < min_L) {
                    min_L = p.second.size();    
                }
            }
            store_buffer_name = read_buffer.substr(1);
                            
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
    

std::pair<std::string, std::string> FastaParser::get_sequence(int index) {
    return sequences[index];
}

size_t FastaParser::num_sequences() {
    return sequences.size();
}
/*
int main(int argc, char** argv) {
    //FastaParser* ref = new FastaParser();
    FastaParser* reads = new FastaParser();
    //ref->parse(argv[1]);
    reads->parse(argv[1]);
    //std::cerr << "Number of reference sequences: " << ref->num_sequences() << "\n";
    std::cerr << "Number of read sequences: " << reads->num_sequences() << "\n";
    //delete ref;
    delete reads;
}
*/




    
