#include <iostream>

#include "opt_parser.h"

OptParser::OptParser(std::unordered_map<std::string, bool> options) {
    this->options = options;
}    

std::vector<std::pair<std::string, std::string>> OptParser::parse(int argc, char** argv, std::vector<std::string>& non_opts, std::vector<std::pair<std::string, std::string>>& bad_opts) {
    std::cout << "parsing\n";
    std::vector<std::pair<std::string, std::string>> opts;
    return opts;
}

//For debugging, will be deleted
int main(int argc, char** argv) {
    std::unordered_map<std::string, bool> m;
    std::vector<std::string> v1;
    std::vector<std::pair<std::string, std::string>> v2;
    OptParser p(m);
    p.parse(argc, argv, v1, v2);
}