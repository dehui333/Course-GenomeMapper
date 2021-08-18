#include <iostream>

#include "opt_parser.h"

OptParser::OptParser(std::unordered_set<Option, OptionHash> options) {
    this->options = options;
}    

std::vector<std::pair<std::string, std::string>> OptParser::parse(int argc, char** argv) {
    std::cout << "parsing!\n";
    std::vector<std::pair<std::string, std::string>> output;
    return output;
}

//For debugging, will be deleted
int main(int argc, char** argv) {
    std::unordered_set<Option, OptionHash> s;
    OptParser p(s);
    p.parse(argc, argv);
}