#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>

#include "align.h"
#include "config.h"
#include "fasta_parser.h"
#include "fastq_parser.h"
#include "opt_parser.h"

bool print_version = false;
bool print_help = false;

std::string ErrorString(std::string opt, int error_code) {
    switch (error_code){
        case KUndefined:
            return opt + " is undefined!\n";
            break;
        case KNoArgument:
            return "Cannot find an argument for " + opt + "!\n";
            break;
        default:
            return "UNKNOWN ERROR CODE\n";
            break;
    }
}

void ProcessOpts(std::vector<std::pair<std::string, std::string>>& opts, std::vector<std::pair<std::string, int>>& bad_opts) {
    for (auto p: opts) {
        if (p.first == "h") {
            print_help = true;
        } else if (p.first == "version") {
            print_version = true;
        }
    }
    for (auto p: bad_opts) {
        std::cerr << ErrorString(p.first, p.second);
    }
}

std::string GetFileExtension(std::string file_path) {
    size_t i = file_path.size() - 1;
    std::string extension = "";
    while (file_path[i] != '.') {
        extension = file_path[i] + extension;
        i--;
        if (i < 0) {
            std::cerr << "Input file should be of FASTA/FASTQ format!\n";
        }
    }
    return extension;
}

void PrintStats(FastaParser* ref, FastaParser* r1, FastqParser* r2) {
    int max_L_reads;
    int min_L_reads;
    float average_L_reads;
    size_t total_num_reads = r1->NumSequences() + r2->NumSequences();
    max_L_reads = r1-> MaxL() >= r2->MaxL() ? r1->MaxL() : r2->MaxL();
    min_L_reads = r1-> MinL() <= r2->MinL() ? r1->MinL() : r2->MinL();
    size_t sum_L_reads = 0;
    std::vector<std::pair<size_t, std::string>> to_sort;
    to_sort.reserve(total_num_reads);
    for (int i = 0; i < r1->NumSequences(); i++) {
        std::string seq = r1->GetSequence(i);
        size_t size = seq.size();
        sum_L_reads += size;
        to_sort.push_back(std::make_pair(-size, seq)); 
    }
    for (int i = 0; i < r2->NumSequences(); i++) {
        std::string seq = r2->GetSequence(i);
        size_t size = seq.size();
        sum_L_reads += size;
        to_sort.push_back(std::make_pair(-size, seq));
    }
    average_L_reads = static_cast<float>(sum_L_reads)/total_num_reads;
    std::sort(to_sort.begin(), to_sort.end());
    float half_way = static_cast<float>(sum_L_reads)/2;
    float sum = 0;
    size_t N50;
    for (auto p:to_sort) {
        sum+=-p.first;
        if (sum >= half_way) {
            N50 = -p.first;
            break;
        }
        
    }
    
    
    std::cerr << "Reference sequence(s): \n";
    std::cerr << "Num sequences: " << ref->NumSequences() << "\n";
    std::cerr << "Min L: " << ref->MinL() << "\n";
    std::cerr << "Max L: " << ref->MaxL() << "\n";
    std::cerr << "Avg L: " << ref->AverageL() << "\n";
    std::cerr << "Fragments: \n";
    std::cerr << "Num sequences: "<< total_num_reads << "\n";
    std::cerr << "Min L: " << min_L_reads << "\n";
    std::cerr << "Max L: " << max_L_reads << "\n";
    std::cerr << "Avg L: " << average_L_reads << "\n";
    std::cerr << "N50: " << N50 << "\n";
}

void ProcessNonOpts(std::vector<std::string>& non_opts) {
    
    if (non_opts.empty()) {
        return;
    }
    FastaParser* ref = new FastaParser();
    FastaParser* reads_fasta = new FastaParser();
    FastqParser* reads_fastq = new FastqParser();
    ref->Parse(non_opts[0]);
    for (int i = 1; i < non_opts.size(); i++) {
        std::string extension = GetFileExtension(non_opts[i]);
        if (extension == "fasta") {
            reads_fasta->Parse(non_opts[i]);        
        } else if (extension == "fastq") {
            reads_fastq->Parse(non_opts[i]);
        } else {
            std::cerr << "Unknown file format: " << extension << "\n"; 
        }
        
    }
    PrintStats(ref, reads_fasta, reads_fastq);
    
    delete ref;
    delete reads_fasta;
    delete reads_fastq;
    
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
    auto opts = p.Parse(argc, argv_string, non_opts, bad_opts);
    ProcessOpts(opts, bad_opts);
    ProcessNonOpts(non_opts);
    
    if (print_version) {
        std::cout << "The current version is " << VERSION_MAJOR << "." << VERSION_MINOR << "." << VERSION_PATCH << "\n";
    }
    
    if (print_help) {
        std::cout << "Please enter the path to the reference sequence followed by one or more path(s) to fragment sequences as arguments.\n";
        std::cout << "e.g. ./mist_mapper ref.fasta frag1.fasta frag2.fasta\n";
    }

    
    return 0;

}
