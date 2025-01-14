#include <iostream>
#include <utility>
#include <vector>

#include "align.h"

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
        std::string* cigar,
        unsigned int* target_begin
        ) {
        
        switch (type) {
            
            case AlignmentType::KGlobal:
                return AlignGlobal(query, query_len, target, target_len, match, mismatch, gap, num_match, num_mismatch, num_ins, num_del, cigar, target_begin);
                break;
            case AlignmentType::KLocal:
                return AlignLocal(query, query_len, target, target_len, match, mismatch, gap, num_match, num_mismatch, num_ins, num_del, cigar, target_begin);
                break;
            case AlignmentType::KSemiGlobal:
                return AlignSemiGlobal(query, query_len, target, target_len, match, mismatch, gap, num_match, num_mismatch, num_ins, num_del, cigar, target_begin);
                break;
            default:
                std::cerr << "Unknown alignment type\n";
                return -1;
        }
        
        
    }
    
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
        std::string* cigar,
        unsigned int* target_begin
        ) {
            
        
        int matrix[query_len + 1][target_len + 1];
        for (unsigned int i = 0; i <= query_len; i++) {
            for (unsigned int j = 0; j <= target_len; j++) {
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
        if (target_begin != nullptr) {
            *target_begin = 0;
        }
        std::string s = "";
        int i = query_len;
        int j = target_len;
        int count = 0;
        char c = '?';
        char current_c;
        
        while (i != 0 || j != 0) {
            if (i == 0) {
                j--;
                current_c = 'D';
                      
            } else if (j == 0) {
                i--;
                current_c = 'I';
                
            } else {
                //0 for move left, 1 for move up, 2 for move diagonal 
                int move = 2;
                if (matrix[i][j] == matrix[i][j-1] + gap) {
                    move = 0;
                } else if (matrix[i][j] == matrix[i-1][j] + gap) {
                    move = 1;
                }
             
                if (move == 0) {
                    j--;
                    current_c = 'D';
                    
                } else if (move == 1) {
                    i--;
                    current_c = 'I';
                    
                } else {
                    i--;
                    j--;
                    current_c = query[i] == target[j] ? '=' : 'X';                 
                    
                }
                
            }
            if (current_c != c) {
                    if (count != 0) {
                        s = std::to_string(count) + c + s;
                        if (c == '=') {
                            num_match += count;
                        } else if (c == 'X') {
                            num_mismatch += count;
                        } else if (c == 'D') {
                            num_del += count;
                        } else if (c == 'I') {
                            num_ins += count;
                        }
                    }
                    c = current_c;
                    count = 1;
            } else {
                count++;    
            }
            
        }
        if (count != 0) {
            s = std::to_string(count) + c + s;
            if (c == '=') {
                num_match += count;
            } else if (c == 'X') {
                num_mismatch += count;
            } else if (c == 'D') {
                num_del += count;
            } else if (c == 'I') {
                num_ins += count;
            }
        }
        if (cigar != nullptr) {
            *cigar = s;
        }
        
            
        return matrix[query_len][target_len];     
        
    }
    
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
        std::string* cigar,
        unsigned int* target_begin
        ) {
            
        int matrix[query_len + 1][target_len + 1];
        for (unsigned int i = 0; i <= query_len; i++) {
            for (unsigned int j = 0; j <= target_len; j++) {
                if (i == 0) {
                    matrix[i][j] = 0;
                } else if (j == 0) {
                    matrix[i][j] = 0;
                } else {
                    //Last position
                    int match_score = query[i-1] == target[j-1] ? match : mismatch;
                    int if_match = match_score + matrix[i-1][j-1];
                    int if_del = gap + matrix[i-1][j];
                    int if_ins = gap + matrix[i][j-1];
                    int max = if_match > if_del ? if_match : if_del;
                    max = max > if_ins ? max : if_ins;
                    max = max > 0 ? max : 0;
                    matrix[i][j] = max;
                    
                }
            }
        }
        unsigned int i;
        unsigned int j;
        int score = INT32_MIN;
        for (unsigned int u = 0; u <= query_len; u++) {
            for (unsigned int v = 0; v <= target_len; v++) {
                if (matrix[u][v] > score) {
                    score = matrix[u][v];
                    i = u;
                    j = v;
                    
                }
                
            }

        }
        int num_S_right = query_len - i;    
        
        std::string s = "";
        int count = 0;
        char c = '?';
        char current_c;
        
        while (matrix[i][j] != 0) {
            unsigned int temp_j = j;
            if (i == 0) {
                j--;
                current_c = 'D';
                      
            } else if (j == 0) {
                i--;
                current_c = 'I';
                
            } else {
                
                //0 for move left, 1 for move up, 2 for move diagonal 
                int move = 2;
                if (matrix[i][j] == matrix[i][j-1] + gap) {
                    move = 0;
                } else if (matrix[i][j] == matrix[i-1][j] + gap) {
                    move = 1;
                }
                if (move == 0) {
                    j--;
                    current_c = 'D';
                    
                } else if (move == 1) {
                    i--;
                    current_c = 'I';
                    
                } else {
                    i--;
                    j--;
                    current_c = query[i] == target[j] ? '=' : 'X';                 
                    
                }
                
            }
            if (current_c != c) {
                    if (count != 0) {
                        s = std::to_string(count) + c + s;
                        if (c == '=') {
                            num_match += count;
                        } else if (c == 'X') {
                            num_mismatch += count;
                        } else if (c == 'D') {
                            num_del += count;
                        } else if (c == 'I') {
                            num_ins += count;
                        }
                    }
                    c = current_c;
                    count = 1;
            } else {
                count++;    
            }
            if (matrix[i][j] == 0) {
                if (target_begin != nullptr) {
                    *target_begin = temp_j - 1;
                }
            }
            
        }
        int num_S_left = i;
        if (count != 0) {
            s = std::to_string(count) + c + s;
            if (c == '=') {
                num_match += count;
            } else if (c == 'X') {
                num_mismatch += count;
            } else if (c == 'D') {
                num_del += count;
            } else if (c == 'I') {
                num_ins += count;
            }
            
        }
        std::string left_append = "";
        std::string right_append = "";
        if (num_S_left != 0) {
            left_append = std::to_string(num_S_left) + "S";
        }
        if (num_S_right != 0) {
            right_append = std::to_string(num_S_right) + "S";
        }
        
        if (cigar != nullptr) {
            *cigar = left_append + s + right_append;
        }
        
            
        return score;      
        
        
    }
    
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
        std::string* cigar,
        unsigned int* target_begin
        ) {
        int score = AlignGlobal(query, query_len, target, target_len, match, mismatch, gap, num_match, num_mismatch, num_ins, num_del, cigar, target_begin);
        if (cigar->empty()) {
            return score;
        }
        std::vector<std::pair<char, int>> chars; //chars in cigar and their positions
        for (int i = 0; i < cigar->size(); i++) {
            
            if (!isdigit((*cigar)[i])) {
                chars.push_back(std::make_pair((*cigar)[i], i));
            }
        }

        
        if (chars[0].first == 'D' || chars[0].first == 'I') {
            std::string num_string = cigar->substr(0, chars[0].second);
            int number = stoi(num_string);
            score -= number * gap;
            
        }
        
        
        int last_index = chars.size() - 1;
        if (chars[last_index].first == 'D' || chars[last_index].first == 'I') {
            if (chars[last_index].second == chars[0].second) {
                return score;
            }
            int second_last_char_position = chars[last_index-1].second+1;
            int l = cigar->size() - second_last_char_position - 1;
            std::string num_string = cigar->substr(second_last_char_position, l);
            int number = stoi(num_string);
            score -= number * gap;
            
        }
        
        
        return score;
    }
        
    
    
}