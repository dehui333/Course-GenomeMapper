#include <iostream>

#include "opt_parser.h"


OptParser::OptParser(std::unordered_map<std::string, bool> options) {
    this->options_ = options;
}    

std::vector<std::pair<std::string, std::string>> OptParser::Parse(int argc, std::string argv[], std::vector<std::string>& non_opts, std::vector<std::pair<std::string, int>>& bad_opts) {
    std::vector<std::pair<std::string, std::string>> opts;
    bool needs_argument;
    for (int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if (IsNonOpt(s)) {
            non_opts.push_back(s);
            
        } else {
            if (IsPotentialShortOpt(s)) {
                if (IsShortOpt(s, needs_argument)) {
                    std::string opt_code = s.substr(1);
                    if (!needs_argument) {
                        opts.push_back(make_pair(opt_code, ""));
                        continue;
                    }
                    
                    i++;
                    if (i >= argc) {
                        bad_opts.push_back(make_pair(s, KNoArgument));
                        break;
                    }
                    std::string potential_argument = argv[i];
                    if (IsNonOpt(potential_argument)) {
                        opts.push_back(make_pair(opt_code, potential_argument));
                    } else {
                        bad_opts.push_back(make_pair(s, KNoArgument));
                        i--;
                    }
                } else {
                    bad_opts.push_back(make_pair(s, KUndefined));
                }
                
            } else if (IsPotentialLongOpt(s)) {
                if (IsLongOpt(s, needs_argument)) {
                    std::string opt_code = s.substr(2);
                    if (!needs_argument) {
                        opts.push_back(make_pair(opt_code, ""));
                        continue;
                    }
                    i++;
                    if (i >= argc) {
                        bad_opts.push_back(make_pair(s, KUndefined));
                        break;
                    }
                    std::string potential_argument = argv[i];
                    if (IsNonOpt(potential_argument)) {
                        opts.push_back(make_pair(opt_code, potential_argument));
                    } else {
                        bad_opts.push_back(make_pair(s, KNoArgument));
                        i--;
                    }
                } else {
                    bad_opts.push_back(make_pair(s, KUndefined));
                }
                
            }
            
        }
    }
    
    return opts;
}

bool OptParser::IsPotentialShortOpt(std::string s) {
   if (s.size() < 2) {
       return false;
   }
   return s[0] == '-' && isalpha(s[1]);
}

bool OptParser::IsPotentialLongOpt(std::string s) {
    if (s.size() < 3) {
        return false;
    }
    return s[0] == '-' && s[1] == '-' && isalpha(s[2]);
}

bool OptParser::IsShortOpt(std::string s, bool& needs_argument) {
    if (!IsPotentialShortOpt(s) || s.size() > 2) {
        return false;
    }
    std::string potential_opt = s.substr(1);
    auto iter = options_.find(potential_opt);
    if (iter != options_.end()) {
        needs_argument = iter->second;
        return true;
    } else {
        return false;
    }
    
}

bool OptParser::IsLongOpt(std::string s, bool& needs_argument) {
    if (!IsPotentialLongOpt(s) || s.size() < 4) {
        return false;
    }
    std::string potential_opt = s.substr(2);
    auto iter = options_.find(potential_opt);
    if (iter != options_.end()) {
        needs_argument = iter->second;
        return true;
    } else {
        return false;
    }
}

bool OptParser::IsNonOpt(std::string s) {
    return !(IsPotentialLongOpt(s) || IsPotentialShortOpt(s));
}