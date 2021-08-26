#include <climits>
#include <fstream>
#include <iostream>
#include <string>

#include "config.h"
#include "FastaParser.h"
#include "FastqParser.h"
#include "OptParser.h"

bool print_version = false;
bool print_help = false;

std::string error_string(std::string opt, int error_code) {
    switch (error_code){
        case UNDEFINED:
            return opt + " is undefined!\n";
            break;
        case NO_ARGUMENT:
            return "Cannot find an argument for " + opt + "!\n";
            break;
        default:
            return "UNKNOWN ERROR CODE\n";
            break;
    }
}

void process_opts(std::vector<std::pair<std::string, std::string>>& opts, std::vector<std::pair<std::string, int>>& bad_opts) {
    for (auto p: opts) {
        if (p.first == "h") {
            print_help = true;
        } else if (p.first == "version") {
            print_version = true;
        }
    }
    for (auto p: bad_opts) {
        std::cerr << error_string(p.first, p.second);
    }
}

void process_non_opts(std::vector<std::string>& non_opts) {
    
    if (non_opts.empty()) {
        return;
    }
    BioSequenceParser* ref = new FastaParser();
    BioSequenceParser* reads = new FastaParser();
    ref->parse(non_opts[0]);
    for (int i = 1; i < non_opts.size(); i++) {
        reads->parse(non_opts[i]);
    }
    std::cerr << "Number of reference sequences: " << ref->num_sequences() << "\n";
    std::cerr << "Number of read sequences: " << reads->num_sequences() << "\n";
    
    delete ref;
    delete reads;
    
}

int main(int argc, char** argv) {
    
    std::unordered_map<std::string, bool> m = {{"h", false}, {"version", false}};
    std::vector<std::string> non_opts;
    std::vector<std::pair<std::string, int>> bad_opts;
    OptParser p(m);
    std::string argv_string[argc];
    for (int i = 0; i < argc; i++) {
        argv_string[i] = argv[i];
    }
    auto opts = p.parse(argc, argv_string, non_opts, bad_opts);
    process_opts(opts, bad_opts);
    process_non_opts(non_opts);
    
    if (print_version) {
        std::cout << "The current version is " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "\n";
    }
    
    if (print_help) {
        std::cout << "Please enter the path to the reference sequence followed by one or more path(s) to fragment sequences as arguments.\n";
        std::cout << "e.g. ./mist_mapper ref.fasta frag1.fasta frag2.fasta\n";
    }

    
    return 0;

}
