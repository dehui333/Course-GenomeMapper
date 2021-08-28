#include <fstream>
#include <iostream>

#include "fasta_parser.h"

void FastaParser::parse(std::string path) {
    std::ifstream input_file(path);
    std::string read_buffer;
    std::string store_buffer_name;
    std::string store_buffer_sequence = "";
    while (getline(input_file, read_buffer)) {
        if (read_buffer[0] == '>') {
         
            if (store_buffer_sequence != "") {
                std::pair<std::string, std::string> p (store_buffer_name, store_buffer_sequence);
                sequences.push_back(p);
                store_buffer_sequence = "";
                average_L += (p.second.size() - average_L) / sequences.size();
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
                average_L += (p.second.size() - average_L) / sequences.size();
                if (p.second.size() > max_L) {
                    max_L = p.second.size();
                } 
                if (p.second.size() < min_L) {
                    min_L = p.second.size();    
                }
    }
    

}
    

std::string FastaParser::get_sequence(size_t i) {
    return sequences[i].second;
}

std::string FastaParser::get_description(size_t i) {
    return sequences[i].first;
}


size_t FastaParser::num_sequences() {
    return sequences.size();
}
/*
int main(int argc, char** argv) {
    std::string prefix = "../../data/";
    FastaParser* reads = new FastaParser();
    reads->parse(prefix + "test1.fasta");
    std::cout << "num_sequences " << reads->num_sequences() << "\n";
    std::cout << "min L " << reads->min_L << "\n";
    std::cout << "max L " << reads->max_L << "\n";
    std::cout << "avg L " << reads->average_L << "\n";
    
    reads->parse(prefix + "test2.fasta");
    std::cout << "num_sequences " << reads->num_sequences() << "\n";
    std::cout << "min L " << reads->min_L << "\n";
    std::cout << "max L " << reads->max_L << "\n";
    std::cout << "avg L " << reads->average_L << "\n";
    delete reads;    
    
}
*/




    
