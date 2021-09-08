#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>

#include "align.h"
#include "config.h"
#include "fasta_parser.h"
#include "fastq_parser.h"
#include "minimizer.h"
#include "opt_parser.h"

bool print_version = false;
bool print_help = false;
bool calculate_alignment = false;
AlignmentType type = AlignmentType::KGlobal;
int match_cost = 3;
int mismatch_cost = -5;
int gap_cost = -4;
int kmer_size = 15;
int window_size = 10;
int cluster_band_size = 10;
double filter = 0.001;

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

bool is_int_string(std::string s) {
    bool arg_is_int_string = true;
    for (int i = 0; i < s.size();i++) {
        if (!isdigit(s[i])) {
            arg_is_int_string = false;
            break;
        }
    }
    return arg_is_int_string;
}

bool is_float_string(std::string s) {
    if (!isdigit(s[0])) {
        return false;
    }
    bool arg_is_float_string = true;
    for (int i = 1; i < s.size();i++) {
        if (!(isdigit(s[i]) || s[i] == '.')) {
            arg_is_float_string = false;
            break;
        }
    }
    return arg_is_float_string;
    
}

void ProcessOpts(std::vector<std::pair<std::string, std::string>>& opts, std::vector<std::pair<std::string, int>>& bad_opts) {
    for (auto p: opts) {
        std::string opt = p.first;
        std::string arg = p.second;
        if (opt == "h") {
            print_help = true;
        } else if (opt == "version") {
            print_version = true;
        } else if (opt == "c") {
            calculate_alignment = true;
        } else if (opt == "m") {
            if (is_int_string(arg)) {
                match_cost = std::stoi(arg);
            } else {
                std::cerr << "-m requires an integer argument!\n";
            }
            
        } else if (opt == "n") {
            if (is_int_string(arg)) {
                mismatch_cost = std::stoi(arg);
            } else {
                std::cerr << "-n requires an integer argument!\n";
            }
        } else if (opt == "g") {
            if (is_int_string(arg)) {
                gap_cost = std::stoi(arg);
            } else {
                std::cerr << "-g requires an integer argument!\n";
            }
        } else if (opt == "k") {
            if (is_int_string(arg)) {
                kmer_size = std::stoi(arg);
            } else {
                std::cerr << "-k requires an integer argument <= 16!\n";
            }
        } else if (opt == "w") {
            if (is_int_string(arg)) {
                window_size = std::stoi(arg);
            } else {
                std::cerr << "-w requires an integer argument!\n";
            }
        } else if (opt == "f") {
            if (is_float_string(arg)) {
                filter = std::stod(arg);
            } else {
                std::cerr << "-f requires a floating point argument!\n";
            }
        } else if (opt == "a") {
            if (arg == "global") {
                type = AlignmentType::KGlobal;
            } else if (arg == "local") {
                type = AlignmentType::KLocal;
            } else if (arg == "semi") {
                type = AlignmentType::KSemiGlobal;
            } else {
                std::cerr << "-a requires an argument out of 1. global 2. local 3. semi\n";
            }
        } else if (opt == "b") {
            if (is_int_string(arg)) {
                cluster_band_size = std::stoi(arg);
            } else {
                std::cerr << "-b requires an integer argument!\n";
            }
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
void MapAndPrintResults(
    std::vector<std::string>& reads, 
    std::vector<std::string>& names,
    std::vector<std::string>& refs,
    std::vector<std::string>& refs_names,
    std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>>& hash_map,
    std::unordered_map<unsigned int, unsigned int>& hash_count,
    unsigned int& total_count) {
        for (int i = 0; i < reads.size(); i++) {
            
            
            std::string the_query = reads[i];
            unsigned int query_len = reads[i].size();
        
            
            std::vector<std::tuple<unsigned int, bool, unsigned int, unsigned int, unsigned int, unsigned int>> overlaps = 
                mist::Map(the_query.c_str(), query_len, kmer_size, window_size, cluster_band_size, filter, hash_map, hash_count, total_count);   
            
            for (auto t: overlaps) {
                unsigned int num_match = 0;
                unsigned int num_mismatch = 0;
                unsigned int num_ins = 0;
                unsigned int num_del = 0;
                std::string output_string = "";
                std::string cigar = "";    
                /*std::cout << names[i] << "\n";
                std::cout << "target: " << refs_names[std::get<0>(t)] << "\n";
                std::cout << "diff strand? " << std::get<1>(t) << "\n";
                std::cout << "q start " << std::get<2>(t) << "\n";
                std::cout << "q end exclusive " << std::get<3>(t) + kmer_size<< "\n";
                std::cout << "t start " << std::get<4>(t) << "\n";
                std::cout << "t end exclusive " << std::get<5>(t) + kmer_size<< "\n";*/
                output_string += names[i] + "\t";
                output_string += std::to_string(query_len) + "\t";
                output_string += std::to_string(std::get<2>(t)) + "\t";
                output_string += std::to_string(std::get<3>(t) + kmer_size) + "\t";
                if (std::get<1>(t)) {
                    output_string += "-\t";
                } else {
                    output_string += "+\t";
                }
                output_string += refs_names[std::get<0>(t)] + "\t";
                output_string += std::to_string(refs[std::get<0>(t)].size()) + "\t";
                output_string += std::to_string(std::get<4>(t)) + "\t";
                output_string += std::to_string(std::get<5>(t) + kmer_size) + "\t";
                if (calculate_alignment) {
                    unsigned int target_end_index_exclusive = std::get<5>(t) + kmer_size; 
                    unsigned int target_len = target_end_index_exclusive - std::get<4>(t);
                    std::string the_target = refs[std::get<0>(t)].substr(std::get<4>(t), target_len);
                    unsigned int target_begin = -1;
                    int alignment_score = mist::Align(the_query.c_str(), query_len, the_target.c_str(), target_len, type, match_cost, mismatch_cost, gap_cost, num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
                    /*std::cout << "score " << alignment_score << "\n";
                    std::cout << "num match " << num_match << "\n";
                    std::cout << "num mismatch " << num_mismatch << "\n";
                    std::cout << "num ins " << num_ins << "\n";
                    std::cout << "num del " << num_del << "\n";
                    std::cout << "cigar " << cigar << "\n";*/
                }
                output_string += std::to_string(num_match) + "\t";
                output_string += std::to_string(num_match+num_mismatch+num_ins+num_del) + "\t";
                output_string += std::to_string(255) + "\t";
                output_string += "cg:Z:" + cigar +"\n";
                std::cout << output_string;
            }
    }
        
        
}

void Map(FastaParser* ref, FastaParser* reads_fasta, FastqParser* reads_fastq) {
    std::vector<std::string> fasta_reads = reads_fasta->GetSequences();
    std::vector<std::string> fastq_reads = reads_fastq->GetSequences();
    std::vector<std::string> fasta_names = reads_fasta->GetDescriptions();
    std::vector<std::string> fastq_names = reads_fastq->GetDescriptions();
    std::vector<std::string> refs = ref->GetSequences();
    std::vector<std::string> refs_names = ref->GetDescriptions();
    std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>> hash_map;
    std::unordered_map<unsigned int, unsigned int> hash_count;
    unsigned int total_count = 0; 
    mist::Minimize(refs, kmer_size, window_size, hash_map, hash_count, total_count);
    MapAndPrintResults(fasta_reads, fasta_names, refs, refs_names, hash_map, hash_count, total_count);    
    MapAndPrintResults(fastq_reads, fastq_names, refs, refs_names, hash_map, hash_count, total_count);
    
    
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
    //PrintStats(ref, reads_fasta, reads_fastq);
    Map(ref, reads_fasta, reads_fastq);
    
    delete ref;
    delete reads_fasta;
    delete reads_fastq;
    
}

int main(int argc, char** argv) {
    
    std::unordered_map<std::string, bool> m = {{"h", false}, {"c", false}, {"a", true}, {"m", true}, {"n", true}, {"g", true},
        {"k", true}, {"w", true}, {"f", true}, {"version", false}, {"b", true}};
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
