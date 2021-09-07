#pragma once

#include <string>

enum class AlignmentType {KGlobal, KLocal, KSemiGlobal};


namespace mist {
    int Align(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        AlignmentType type,
        int match,
        int mismatch,
        int gap,
        unsigned int& num_match,
        unsigned int& num_mismatch,
        unsigned int& num_ins,
        unsigned int& num_del,
        std::string* cigar = nullptr,
        unsigned int* target_begin = nullptr
    );
    
    int AlignGlobal(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        int match,
        int mismatch,
        int gap,
        unsigned int& num_match,
        unsigned int& num_mismatch,
        unsigned int& num_ins,
        unsigned int& num_del,
        std::string* cigar = nullptr,
        unsigned int* target_begin = nullptr
    );
    
    int AlignLocal(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        int match,
        int mismatch,
        int gap,
        unsigned int& num_match,
        unsigned int& num_mismatch,
        unsigned int& num_ins,
        unsigned int& num_del,
        std::string* cigar = nullptr,
        unsigned int* target_begin = nullptr
    );
    
    int AlignSemiGlobal(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        int match,
        int mismatch,
        int gap,
        unsigned int& num_match,
        unsigned int& num_mismatch,
        unsigned int& num_ins,
        unsigned int& num_del,
        std::string* cigar = nullptr,
        unsigned int* target_begin = nullptr
    );
        
    
}
