#include <fstream>
#include <iostream>

#include "FastqParser.h"

void FastqParser::parse(std::string path) {
    /*
    std::ifstream input_file(path);
    std::string read_buffer;
    std::string store_buffer_name;
    std::string store_buffer_sequence = "";
    while (getline(input_file, read_buffer)) {
        
        
    }
*/
    

}
    

std::tuple<std::string, std::string, std::string> FastqParser::get_sequence(int i) {
    return sequences[i];
}

size_t FastqParser::num_sequences() {
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




    
