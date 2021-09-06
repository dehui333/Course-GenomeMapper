#include "minimizer.h"

#include <algorithm>
#include <set>

#include <iostream>

namespace mist {
    void Filter(double prop) {
        filter = prop;
    }
    
    std::tuple<bool, unsigned int, unsigned int, unsigned int, unsigned int> FindOverlap(
        std::vector<std::tuple<unsigned int, bool, int, unsigned int>> roughly_colinear, unsigned int& increasing_len) {
        int highest_value_index = -1;
        std::vector<int> values(roughly_colinear.size(), 2147483647);
        unsigned int indices[roughly_colinear.size()] ={0}; //which input do the elements in the values vector correspond to
        unsigned int parents[roughly_colinear.size()] = {0}; //which input is the parent of each input 
        for (int i = 0; i < roughly_colinear.size(); i++) {
            unsigned int current_input = std::get<3>(roughly_colinear[i]);
            int j = std::upper_bound(values.begin(), values.end(), current_input) - values.begin();
            if (j == 0 || values[j-1] < current_input) {
                values[j] = current_input;
                if (j > highest_value_index) {
                    highest_value_index = j;
                }
                indices[j] = i;
                parents[i] = j == 0 ? -1 : indices[j-1];
                
            } 
        }

        increasing_len = highest_value_index + 1;
        bool diff_strand = std::get<1>(roughly_colinear[0]);
        auto end_tuple = roughly_colinear[indices[highest_value_index]];
        int i = indices[highest_value_index];
        while (parents[i] != -1) {
            i = parents[i];
        }
        auto start_tuple = roughly_colinear[i];
        int mul = diff_strand ? -1 : 1;
        unsigned int query_start = std::get<2>(start_tuple) + mul * std::get<3>(start_tuple);
        unsigned int query_end = std::get<2>(end_tuple) + mul * std::get<3>(end_tuple);
        unsigned int target_start = std::get<3>(start_tuple);
        unsigned int target_end = std::get<3>(end_tuple);
        return std::make_tuple(diff_strand, query_start, query_end, target_start, target_end);
            
            
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
        unsigned int window_len) {
        for (unsigned int i = 0; i < sequences.size(); i++) {
            auto m = Minimize(sequences[i].c_str(), sequences[i].size(), kmer_len, window_len);
            for (auto t: m) {
                unsigned int hash_value = std::get<0>(t);
                if (mist::hash_map.find(hash_value) == mist::hash_map.end()) {
                    std::vector<std::tuple<unsigned int, unsigned int, bool>> v;
                    v.push_back(std::make_tuple(i, std::get<1>(t), std::get<2>(t)));
                    mist::hash_map[hash_value] = v;
                    mist::hash_count[hash_value] = 1;
                    total_count++;
                } else {
                    mist::hash_map[hash_value].push_back(std::make_tuple(i, std::get<1>(t), std::get<2>(t)));
                    mist::hash_count[hash_value]++;
                    total_count++;
                }
                
            }
            
        }       
    }
    
     std::tuple<bool, unsigned int, unsigned int, unsigned int, unsigned int> Map(const char* query, unsigned int sequence_len, unsigned int kmer_len, unsigned int window_len) {
        std::vector<std::tuple<unsigned int, bool, int, unsigned int>> v;
        std::vector<std::tuple<unsigned int, unsigned int, bool>> minimizers_of_query = mist::Minimize(query, sequence_len, kmer_len, window_len);
        unsigned int best_increasing_len = 0;
        std::tuple<bool, unsigned int, unsigned int, unsigned int, unsigned int> best;
        for (auto t: minimizers_of_query) {
            unsigned int hash = std::get<0>(t);
            auto iter = mist::hash_count.find(hash); 
            if (iter != mist::hash_count.end()) {
                double count = static_cast<double>(iter->second);
                double prop = count/total_count;
                if (prop >= filter) {
                    continue;
                }
                std::vector<std::tuple<unsigned int, unsigned int, bool >> hits = mist::hash_map[hash];
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
                    for (auto t: roughly_colinear) {
                        std::cout <<"target num " << std::get<0>(t) << "\n";
                        std::cout <<"diff strand? " << std::get<1>(t) << "\n";
                        std::cout <<"displacement " << std::get<2>(t) << "\n";
                        std::cout <<"target_position " << std::get<3>(t) << "\n\n";
                    }
                    i = j + 1;
                    unsigned int increasing_len = 0;
                    auto overlap = FindOverlap(roughly_colinear, increasing_len);
                    std::cout << "INCREASE " << increasing_len << "\n";
                    std::cout << "BEST INCREASE " << best_increasing_len << "\n";
                    if (increasing_len > best_increasing_len) {
                        best = overlap;
                        best_increasing_len = increasing_len;
                    }
                    std::cout << "--------------------\n";
                    
                }                    
        }
        return best;

    }
}


int main(int argc, char** argv) {
    std::vector<std::string> v = {"ATCGTACATCATTGTA", "AATGTACGAT"};
    mist::Minimize(v, 3, 3);
    mist::Map("ATCGTACATT", 10, 3, 3);
}