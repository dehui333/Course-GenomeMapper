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
        
        int matrix[query_len + 1][target_len + 1];
        for (int i = 0; i <= query_len; i++) {
            for (int j = 0; j <= target_len; j++) {
                if (i == 0) {
                    matrix[i][j] = j * gap;
                } else if (j == 0) {
                    matrix[i][j] = i * gap;
                } else {
                    //Last position
                    int match_score = query[i-1] == target[j-1] ? match : mismatch;
                    int if_match = match_score + matrix[i-1][j-1];
                    int if_del = gap + matrix[i-1][j];
                    int if_ins = gap + matrix[i][j-1];
                    int max = if_match > if_del ? if_match : if_del;
                    max = max > if_ins ? max : if_ins;
                    matrix[i][j] = max;
                    
                }
            }
        }
        *target_begin = 0;
        std::string s = "";
        int i = query_len;
        int j = target_len;
        int count = 0;
        std::string c = "";
        std::string current_c;
        
        while (i != 0 || j != 0) {
            if (i == 0) {
                j--;
                current_c = "D";
                      
            } else if (j == 0) {
                i--;
                current_c = "I";
                
            } else {
                //0 for move left, 1 for move up, 2 for move diagonal 
                int move = matrix[i][j-1] > matrix[i-1][j] ? 0 : 1;
                int value = matrix[i][j-1] > matrix[i-1][j] ? matrix[i][j-1] : matrix[i-1][j];
                move = value > matrix[i-1][j-1] ? move : 2;
                if (move == 0) {
                    j--;
                    current_c = "D";
                    
                } else if (move == 1) {
                    i--;
                    current_c = "I";
                    
                } else {
                    i--;
                    j--;
                    current_c = query[i] == target[j] ? "=" : "X";                 
                    
                }
                
            }
            if (current_c != c) {
                    if (count != 0) {
                        s = std::to_string(count) + c + s;
                    }
                    c = current_c;
                    count = 1;
            } else {
                count++;    
            }
            
        }
        if (count != 0) {
            s = std::to_string(count) + c + s;
        }
        *cigar = s;
        
            
        return matrix[query_len][target_len];     
        
        
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