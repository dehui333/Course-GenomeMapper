#pragma once

#include <unordered_map>
#include <utility>
#include <vector>


/*
A class to represent a defined option for the option parser. Each option should have different names. Options with the same name but
different specifications on whether there is an argument leads to undefined behavior.

Let # denote any alphabet.
1. Any string that starts with "-#' will be considered a potential short option(with one character). If "-#" is followed by other characters or 
if "-#" is not defined, it is considered a bad option. If it is defined but not supplied with the needed argument(if any), it is considered
a bad option. 
2. Any string that starts with "--#" will be considered a potential long option(with more than one character). if "--#" with all the characters
after it is not defined, it is considered a bad option. If it is defined but not supplied with the needed argument(if any), it is considered
a bad option. 
3. Strings that do not start with "-#" or "--#" are non options.
*/



class OptParser {

private:
    std::unordered_map<std::string, bool> options;
    
    
public:         
    
    OptParser(std::unordered_map<std::string, bool> options);
    
    std::vector<std::pair<std::string, std::string>> parse(int argc, char** argv, std::vector<std::string>& non_opts, std::vector<std::pair<std::string, std::string>>& bad_opts);

    


    
    
};