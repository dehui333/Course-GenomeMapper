#pragma once

#include <unordered_set>
#include <utility>
#include <vector>


/*
A class to represent a defined option for the option parser. Each option should have different names. Options with the same name but
different specifications on whether there is an argument leads to undefined behavior.
*/

class Option {
public:
    std::string name;
    bool has_argument;
    
    Option(std::string name, bool has_argument) {
        this->name = name;
        this->has_argument = has_argument;
    }
    
    bool operator==(const Option &o) const {
        return name == o.name;
    }
                
};

class OptionHash {
public:
    std::size_t operator() (const Option& o) const {
        return std::hash<std::string>{}(o.name);
    }
    
};


class OptParser {

private:
    std::unordered_set<Option, OptionHash> options;
public:         
    
    OptParser(std::unordered_set<Option, OptionHash> options);
    
    std::vector<std::pair<std::string, std::string>> parse(int argc, char** argv);




    
    
};