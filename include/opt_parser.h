#pragma once

#include <unordered_map>
#include <utility>
#include <vector>


/*
A class to represent a defined option for the option parser. Each option should have different names. Options with the same name but
different specifications on whether there is an argument leads to undefined behavior.
*/



class OptParser {

private:
    std::unordered_map<std::string, bool> options;
public:         
    
    OptParser(std::unordered_map<std::string, bool> options);
    
    std::vector<std::pair<std::string, std::string>> parse(int argc, char** argv, std::vector<std::string>& non_opts, std::vector<std::pair<std::string, std::string>>& bad_opts);




    
    
};