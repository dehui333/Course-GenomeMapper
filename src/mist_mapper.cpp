#include <climits>
#include <fstream>
#include <getopt.h>
#include <iostream>
#include <string>

#include "config.h"
#include "fasta_parser.h"


int main(int argc, char** argv) {
    int print_version = 0;
    int print_help = 0;
    struct option long_options[] = {
        {"version", no_argument, &print_version, 1},
        {0, 0, 0, 0}
        
    };
    int option_index = 0;
    int out;
    while ((out = getopt_long(argc, argv, ":h", long_options, &option_index)) != -1) {
        switch (out) {
            case 0:
                if (long_options[option_index].flag != 0) {
                    break;
                }
            case 'h':
                std::cout << "Please enter the path to the reference sequence followed by one or more path(s) to fragment sequences as arguments.\n";
                std::cout << "e.g. ./mist_mapper ref.fasta frag1.fasta frag2.fasta\n";
                break;
            case '?':
                std::cout << "Unknown option: " << static_cast<char>(optopt) << "\n";
                break;
            case ':':
                std::cout << "Option with no argument: " << static_cast<char>(optopt) << "\n";
                break;
            default:
                break;     
        }    
    }
    if (print_version) {
        std::cout << "The current version is " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "\n";
    }
    
    
    
    
    
    return 0;

}
