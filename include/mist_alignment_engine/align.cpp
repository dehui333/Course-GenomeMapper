#include <iostream>

#include "align.h"

namespace mist {
    
    int Align(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        AlignmentType type,
        int match,
        int mismatch,
        int gap,
        std::string* cigar,
        unsigned int* target_begin) {
        
        switch (type) {
            
            case AlignmentType::global:
                AlignGlobal(query, query_len, target, target_len, match, mismatch, gap, cigar, target_begin);
                break;
            case AlignmentType::local:
                AlignLocal(query, query_len, target, target_len, match, mismatch, gap, cigar, target_begin);
                break;
            case AlignmentType::semi_global:
                AlignSemiGlobal(query, query_len, target, target_len, match, mismatch, gap, cigar, target_begin);
                break;
            default:
                std::cerr << "Unknown alignment type\n";          
        }
        
    }
    
    int AlignGlobal(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        int match,
        int mismatch,
        int gap,
        std::string* cigar,
        unsigned int* target_begin) {
            
        return 0;     
        
        
    }
    
    int AlignLocal(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        int match,
        int mismatch,
        int gap,
        std::string* cigar,
        unsigned int* target_begin) {
            
        return 0;        
        
        
    }
    
    int AlignSemiGlobal(  
        const char* query, unsigned int query_len,
        const char* target, unsigned int target_len,
        int match,
        int mismatch,
        int gap,
        std::string* cigar,
        unsigned int* target_begin) {
            
        return 0;    
            
            
        }
    
    
}