#include "minimizer.h"

#include <algorithm>
#include <cmath>
#include <set>

#include <iostream>

namespace mist {
    std::tuple<unsigned int, bool, unsigned int, unsigned int, unsigned int, unsigned int> FindOverlap(
        std::vector<std::tuple<unsigned int, bool, int, unsigned int>> roughly_colinear, unsigned int& increasing_len) {
        bool diff_strand = std::get<1>(roughly_colinear[0]);    
        int mul = diff_strand ? -1 : 1;
        int highest_position_index= -1; //points to the largest position  reached
        int highest_input_index = -1; //points to the input object that has the highest value reached
        std::vector<int> values(roughly_colinear.size(), 2147483647); //Longest increasing subsequence of target position values
        unsigned int indices[roughly_colinear.size()]; //which input do the elements in the values vector correspond to
        unsigned int parents[roughly_colinear.size()]; //which input is the parent of each input 
        for (int i = 0; i < roughly_colinear.size(); i++) {
            unsigned int current_input = std::get<3>(roughly_colinear[i]); //current target position
            int j = std::upper_bound(values.begin(), values.end(), current_input) - values.begin();
            unsigned int current_query_pos = std::get<2>(roughly_colinear[i]) + mul * std::get<3>(roughly_colinear[i]);

            if (j != 0) {
                //avoid forming chain with constant query positions
                auto previous = roughly_colinear[indices[j-1]];
                unsigned int previous_query_pos = std::get<2>(previous) + mul * std::get<3>(previous);
                    
                

                if (values[j-1] < current_input) {
                    values[j] = current_input;
                    indices[j] = i;
                    //std::cout << "replaced values[" <<j <<"] index with " << i  << "\n";
                    parents[i] = j == 0 ? -1 : indices[j-1];
                    if (j > highest_position_index) {
                        highest_position_index= j;
                        highest_input_index = indices[j];
                    }
                } 
                
            } else {
                values[j] = current_input;
                indices[j] = i;
                //std::cout << "replaced values[" <<j <<"] index with " << i  << "\n";
                parents[i] = j == 0 ? -1 : indices[j-1];
                if (j > highest_position_index) {
                    highest_position_index= j;
                    highest_input_index = indices[j];
                }
                
            }
        }

        increasing_len = highest_position_index+ 1;
        
        auto end_tuple = roughly_colinear[highest_input_index];
        int i = highest_input_index;
        //std::cout << "trace " << i << "\n"; 
        while (parents[i] != -1) {
            i = parents[i];
            //std::cout << "trace " << i << "\n";
        }
        auto start_tuple = roughly_colinear[i];
        //std::cout << "S index " << i << "\n";
        //std::cout << "E index " << highest_input_index<< "\n";
        auto query_start_tuple = diff_strand ? end_tuple : start_tuple;
        auto query_end_tuple = diff_strand ? start_tuple : end_tuple;
        unsigned int query_start = std::get<2>(query_start_tuple) + mul * std::get<3>(query_start_tuple);
        unsigned int query_end = std::get<2>(query_end_tuple) + mul * std::get<3>(query_end_tuple);
        unsigned int target_start = std::get<3>(start_tuple);
        unsigned int target_end = std::get<3>(end_tuple);
        unsigned int target_index = std::get<0>(end_tuple);
        return std::make_tuple(target_index, diff_strand, query_start, query_end, target_start, target_end);
            
            
    }
  
    
    //A - 00 C - 01 G - 10 T - 11
    unsigned int KmerHash(const char* sequence, unsigned int kmer_len, unsigned int start, bool is_original) {
        unsigned int hash = 0;
        unsigned int end = start + kmer_len - 1;
        if (!is_original) {
            for (int i = 0; i < kmer_len; i++) {
                char c = sequence[end - i];
                if (c == 'A') {
                    hash += 3;
                    hash = hash << 2;
                } else if (c == 'C') {
                    hash += 2;
                    hash = hash << 2;
                } else if (c == 'G') {
                    hash += 1;
                    hash = hash << 2;    
                } else {
                    hash = hash << 2;
                }
            }
            
        } else {
            for (int i = 0; i < kmer_len; i++) {
                char c = sequence[start + i];
                if (c == 'A') {
                    hash = hash << 2;
                } else if (c == 'C') {
                    hash += 1;
                    hash = hash << 2;
                } else if (c == 'G') {
                    hash += 2;
                    hash = hash << 2;    
                } else {
                    hash += 3;
                    hash = hash << 2;
                }
            }
            
            
        }
        hash = ~hash + (hash << 15);
        hash = hash ^ (hash >> 12);
        hash = hash + (hash << 2);
        hash = hash ^ (hash >> 4);
        hash = hash * 2057; 
        hash = hash ^ (hash >> 16);
        return hash;
    }
    
    
    

    std::vector<std::tuple<unsigned int, unsigned int, bool>> Minimize(
        const char* sequence, 
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len) {
        
        
        std::set<std::tuple<unsigned int, unsigned int, bool>> minimizers_set;
        
        for (unsigned int window_start = 0; window_start <= sequence_len - window_len; window_start++) {
            //std::cout << window_start << "\n";
            unsigned int window_min = UINT32_MAX;
            std::set<std::tuple<unsigned int, unsigned int, bool>> minimizers_in_window;
            unsigned int window_end = window_start + window_len - 1;
            for (unsigned int kmer_start = window_start; kmer_start <= window_end - kmer_len + 1; kmer_start++) {
                unsigned int original_value = mist::KmerHash(sequence, kmer_len, kmer_start, true);
                unsigned int reverse_complement_value = mist::KmerHash(sequence, kmer_len, kmer_start, false);
                //std::cout <<"original " << original_value << "\n";
                //std::cout <<"complement " << reverse_complement_value << "\n";
                if (original_value != reverse_complement_value) {
                    unsigned int smaller = original_value < reverse_complement_value ? original_value : reverse_complement_value;
                    bool is_original = original_value < reverse_complement_value ? true : false;
                    if (smaller < window_min) {
                        window_min = smaller;
                        minimizers_in_window.clear();
                        minimizers_in_window.insert(std::make_tuple(smaller, kmer_start, is_original));
                    } else if (smaller == window_min) {
                        minimizers_in_window.insert(std::make_tuple(smaller, kmer_start, is_original));
                    }                        
                } 
            }
            minimizers_set.insert(minimizers_in_window.begin(), minimizers_in_window.end());
            
            
            
        }
        std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers(minimizers_set.begin(), minimizers_set.end());
        return minimizers;    
          
    }
    
    void Minimize(
        std::vector<std::string> sequences, 
        unsigned int kmer_len,
        unsigned int window_len,
        std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>>& hash_map,
        std::unordered_map<unsigned int, unsigned int>& hash_count,
        unsigned int& total_count) {
        for (unsigned int i = 0; i < sequences.size(); i++) {
            auto m = Minimize(sequences[i].c_str(), sequences[i].size(), kmer_len, window_len);
            for (auto t: m) {
                unsigned int hash_value = std::get<0>(t);
                if (hash_map.find(hash_value) == hash_map.end()) {
                    std::vector<std::tuple<unsigned int, unsigned int, bool>> v;
                    v.push_back(std::make_tuple(i, std::get<1>(t), std::get<2>(t)));
                    hash_map[hash_value] = v;
                    hash_count[hash_value] = 1;
                    total_count++;
                } else {
                    hash_map[hash_value].push_back(std::make_tuple(i, std::get<1>(t), std::get<2>(t)));
                    hash_count[hash_value]++;
                    total_count++;
                }
                
            }
            
        }       
    }
    
     std::tuple<unsigned int, bool, unsigned int, unsigned int, unsigned int, unsigned int> Map(
        const char* query,
        unsigned int sequence_len,
        unsigned int kmer_len,
        unsigned int window_len,
        int cluster_band_size,
        double filter,
        std::unordered_map<unsigned int, std::vector<std::tuple<unsigned int, unsigned int, bool >>>& hash_map,
        std::unordered_map<unsigned int, unsigned int>& hash_count,
        unsigned int& total_count
        ) {
        std::vector<std::tuple<unsigned int, bool, int, unsigned int>> v;
        std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers_of_query = mist::Minimize(query, sequence_len, kmer_len, window_len);
        unsigned int best_increasing_len = 0;
        unsigned int best_len_diff = UINT32_MAX;
        std::tuple<unsigned int, bool, unsigned int, unsigned int, unsigned int, unsigned int> best;
        //for (auto p: mist::hash_count) {
        //    std::cout << p.first << " count " << p.second << "\n"; 
        //}
        //std::cout << total_count << "\n";
        for (auto t: minimizers_of_query) {
            unsigned int hash = std::get<0>(t);
            auto iter = hash_count.find(hash); 
            if (iter != hash_count.end()) {
                double count = static_cast<double>(iter->second);
                double prop = count/total_count;
                //std::cout << "HASH " << hash << "\n";
                //std::cout << "PROP " << prop << "\n";
                if (prop >= filter) {
                    //std::cout << hash << " is filtered!\n";
                    continue;
                }
                std::vector<std::tuple<unsigned int, unsigned int, bool >> hits = hash_map[hash];
                for (auto hit: hits) {
                    unsigned int seq_num = std::get<0>(hit);
                    bool diff_strand = (std::get<2>(hit) != std::get<2>(t));
                    int displacement = diff_strand ? std::get<1>(t) + std::get<1>(hit) : std::get<1>(t) - std::get<1>(hit);
                    unsigned int target_position = std::get<1>(hit);                    
                    v.push_back(std::make_tuple(seq_num, diff_strand, displacement, target_position));
                    
                }
                
            }
            
        }
        
        
  
        std::sort(v.begin(), v.end());
        unsigned int i = 0;
        for (unsigned int j = 0; j < v.size(); j++) {
            if (j == (v.size() - 1) || std::get<0>(v[j+1]) != std::get<0>(v[j]) || std::get<1>(v[j+1]) != std::get<1>(v[j]) 
                || (std::get<2>(v[j+1]) - std::get<2>(v[j])) >= cluster_band_size ) {
                    //from i to j, one cluster
                    //find LIS in cluster
                    std::vector<std::tuple<unsigned int, bool, int, unsigned int>> roughly_colinear;
                    for (int s = i; s <= j; s++) {
                        roughly_colinear.push_back(v[s]);
                            
                    }
                    auto comp = [] (std::tuple<unsigned int, bool, int, unsigned int> const& t1, 
                                    std::tuple<unsigned int, bool, int, unsigned int> const& t2) -> bool 
                                   { 
                                       int pos_on_query1;
                                       int pos_on_query2;
                                       if (std::get<1>(t1) == false) {
                                           pos_on_query1 = std::get<2>(t1) + static_cast<int>(std::get<3>(t1));
                                           pos_on_query2 = std::get<2>(t2) + static_cast<int>(std::get<3>(t2));
                                       } else {
                                           pos_on_query1 = static_cast<int>(std::get<3>(t1)) - std::get<2>(t1);
                                           pos_on_query2 = static_cast<int>(std::get<3>(t2)) - std::get<2>(t2);
                                       }
                                  
                                       
                                       return pos_on_query1 < pos_on_query2;
                                   
                                   };
                    std::sort(roughly_colinear.begin(), roughly_colinear.end(), comp);
                    /*for (int i = 0;i< roughly_colinear.size(); i++) {
                        std::cout << i << "\n";
                        auto t = roughly_colinear[i];
                        std::cout <<"target num " << std::get<0>(t) << "\n";
                        std::cout <<"diff strand? " << std::get<1>(t) << "\n";
                        std::cout <<"displacement " << std::get<2>(t) << "\n";
                        std::cout <<"target_position " << std::get<3>(t) << "\n\n";
                    }*/
                    i = j + 1;
                    unsigned int increasing_len = 0;
                    auto overlap = FindOverlap(roughly_colinear, increasing_len);
                    //std::cout << "INCREASE " << increasing_len << "\n";
                    //std::cout << "BEST INCREASE " << best_increasing_len << "\n";
                    int len_q = std::get<3>(overlap) - std::get<2>(overlap);
                    int len_t = std::get<5>(overlap) - std::get<4>(overlap);
                    unsigned int len_diff = std::abs(len_q - len_t);
                    if (increasing_len > best_increasing_len) {
                        best = overlap;
                        best_increasing_len = increasing_len;
                        best_len_diff = len_diff;
                    } else if (increasing_len == best_increasing_len && len_diff < best_len_diff) {
                        best = overlap;
                        best_increasing_len = increasing_len;
                        best_len_diff = len_diff;
                    }                        
                    //std::cout << "--------------------\n";
                    
                }                    
        }
        /*
        std::cout <<"t index " << std::get<0>(best) << "\n";
        std::cout <<"diff strand? " << std::get<1>(best) << "\n";
        std::cout <<"q start " << std::get<2>(best) << "\n";
        std::cout <<"q end " << std::get<3>(best) << "\n";
        std::cout <<"t start " << std::get<4>(best) << "\n";
        std::cout <<"t end " << std::get<5>(best) << "\n\n";
        */
        return best;

    }
}

/*
int main(int argc, char** argv) {
    std::vector<std::string> v = {"ATCATC"};       
    mist::Minimize(v, 3, 3);
    mist::Map("ATCTTTTTATCATC", 14, 3, 3, 10, 1);
}*/