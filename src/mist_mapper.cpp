#include <fstream>
#include <iostream>
#include <string>

#include "config.h"


int main(int argc, char** argv) {
    
    
    if (argc == 2) {
    //Assume that the user inputs a -h or --version flag    
        std::string flag = argv[1];
        if (flag == "-h") {
            std::cout << "Usage: ./Mist_mapper [path to reference genome data] [path to fragment data 1] [path to fragment data 2] ..." 
            << std::endl << "Example: ./Mist_mapper GCF_000005845.2_ASM584v2_genomic.fna MAP006-1_2D_pass.fasta MAP006-2_2D_pass.fasta"
            << std::endl;
        }
        
        if (flag == "--version") {
            std::cout << "This is version " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << std::endl;
        }
    
    } else {
    //Assumed that the user inputs sequences data     
        //std::string reference_path = argv[1];
        
        
    }
    
    
    return 0;

}
