#include <gtest/gtest.h>
#include "opt_parser/opt_parser.cpp"


std::unordered_map<std::string, bool> m = {{"h", false}, {"version", false}, {"test", true}, {"test2", true}};
std::vector<std::string> non_opts;
std::vector<std::pair<std::string, std::string>> bad_opts;
OptParser p(m);

TEST(OptParserTest, ParsingTest1) {
    non_opts.clear();
    bad_opts.clear();
    int argc = 2;
    std::string argv[] = {"", "-h"};    
    auto opts = p.parse(argc, argv, non_opts, bad_opts);
    std::vector<std::string> non_opts_answer;
    ASSERT_EQ(non_opts, non_opts_answer);
    std::vector<std::pair<std::string, std::string>> opts_answer = {{"h", ""}};
    ASSERT_EQ(opts, opts_answer);
    std::vector<std::pair<std::string, std::string>> bad_opts_answer;
    ASSERT_EQ(bad_opts, bad_opts_answer);    
}