#include <iostream>

#include "opt_parser.h"

OptParser::OptParser(std::unordered_map<std::string, bool> options) {
    this->options = options;
}    

std::vector<std::pair<std::string, std::string>> OptParser::parse(int argc, std::string argv[], std::vector<std::string>& non_opts, std::vector<std::pair<std::string, std::string>>& bad_opts) {
    std::vector<std::pair<std::string, std::string>> opts;
    bool needs_argument;
    for (int i = 1; i < argc; i++) {
        std::string s = argv[i];
        if (is_non_opt(s)) {
            non_opts.push_back(s);
            
        } else {
            if (is_potential_short_opt(s)) {
                if (is_short_opt(s, needs_argument)) {
                    std::string opt_code = s.substr(1);
                    if (!needs_argument) {
                        opts.push_back(make_pair(opt_code, ""));
                        continue;
                    }
                    
                    i++;
                    if (i >= argc) {
                        bad_opts.push_back(make_pair(s, "Cannot find argument for " + s + "!\n"));
                        break;
                    }
                    std::string potential_argument = argv[i];
                    if (is_non_opt(potential_argument)) {
                        opts.push_back(make_pair(opt_code, potential_argument));
                    } else {
                        bad_opts.push_back(make_pair(s, "Cannot find argument for " + s + "!\n"));
                        i--;
                    }
                } else {
                    bad_opts.push_back(make_pair(s, s +" is an undefined option!\n"));
                }
                
            } else if (is_potential_long_opt(s)) {
                if (is_long_opt(s, needs_argument)) {
                    std::string opt_code = s.substr(2);
                    if (!needs_argument) {
                        opts.push_back(make_pair(opt_code, ""));
                        continue;
                    }
                    i++;
                    if (i >= argc) {
                        bad_opts.push_back(make_pair(s, "Cannot find argument for " + s + "!\n"));
                        break;
                    }
                    std::string potential_argument = argv[i];
                    if (is_non_opt(potential_argument)) {
                        opts.push_back(make_pair(opt_code, potential_argument));
                    } else {
                        bad_opts.push_back(make_pair(s, "Cannot find argument for " + s + "!\n"));
                        i--;
                    }
                } else {
                    bad_opts.push_back(make_pair(s, s +" is an undefined option!\n"));
                }
                
            }
            
        }
    }
    
    return opts;
}

bool OptParser::is_potential_short_opt(std::string s) {
   if (s.size() < 2) {
       return false;
   }
   return s[0] == '-' && isalpha(s[1]);
}

bool OptParser::is_potential_long_opt(std::string s) {
    if (s.size() < 3) {
        return false;
    }
    return s[0] == '-' && s[1] == '-' && isalpha(s[2]);
}

bool OptParser::is_short_opt(std::string s, bool& needs_argument) {
    if (!is_potential_short_opt(s) || s.size() > 2) {
        return false;
    }
    std::string potential_opt = s.substr(1);
    auto iter = options.find(potential_opt);
    if (iter != options.end()) {
        needs_argument = iter->second;
        return true;
    } else {
        return false;
    }
    
}

bool OptParser::is_long_opt(std::string s, bool& needs_argument) {
    if (!is_potential_long_opt(s) || s.size() < 4) {
        return false;
    }
    std::string potential_opt = s.substr(2);
    auto iter = options.find(potential_opt);
    if (iter != options.end()) {
        needs_argument = iter->second;
        return true;
    } else {
        return false;
    }
}

bool OptParser::is_non_opt(std::string s) {
    return !(is_potential_long_opt(s) || is_potential_short_opt(s));
}

/*
//For debugging, will be deleted
int main(int argc, char** argv) {
    std::unordered_map<std::string, bool> m = {{"h", false}, {"version", false}, {"test", true}, {"test2", true}};
    std::vector<std::string> non_opts;
    std::vector<std::pair<std::string, std::string>> bad_opts;
    OptParser p(m);
    auto opts = p.parse(argc, argv, non_opts, bad_opts);
    std::cout << "--------options-------\n";
    for (auto p:opts) {
        std::cout << p.first << " " << p.second << "\n";
    }
    std::cout << "--------non opts--------\n";
    for (auto s: non_opts) {
        std::cout << s << "\n"; 
    }
    std::cout << "---------bad opts--------\n";
    for (auto p:bad_opts) {
        std::cout << p.first << " " << p.second << "\n";
    }

}*/