#include <fstream>
#include <iostream>

#include "fastq_parser.h"

void FastqParser::parse(std::string path) {
    
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
                sequences.push_back(std::make_tuple(store_buffer_name, store_buffer_sequence, store_buffer_quality));
                average_L += (store_buffer_sequence.size() - average_L) / sequences.size();
                if (store_buffer_sequence.size() > max_L) {
                    max_L = store_buffer_sequence.size();
                } 
                if (store_buffer_sequence.size() < min_L) {
                    min_L = store_buffer_sequence.size();    
                }
                phase = 0;
                break;
            default:
                std::cerr << "Error in parsing!\n";
                return;
            
            
        }
        
    }

    

}
    

std::string FastqParser::get_sequence(size_t i) {
    return std::get<1>(sequences[i]);
}

std::string FastqParser::get_description(size_t i) {
    return std::get<0>(sequences[i]);
}

std::string FastqParser::get_quality(size_t i) {
    return std::get<2>(sequences[i]);
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




    
