#include <gtest/gtest.h>
#include "OptParser.cpp"

std::unordered_map<std::string, bool> m = {{"h", false}, {"version", false}, {"test", true}, {"test2", true}, {"c", false}};
std::vector<std::string> non_opts;
std::vector<std::pair<std::string, int>> bad_opts;
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
    std::vector<std::pair<std::string, int>> bad_opts_answer;
    ASSERT_EQ(bad_opts, bad_opts_answer);    
}

TEST(OptParserTest, ParsingTest2) {
    non_opts.clear();
    bad_opts.clear();
    int argc = 4;
    std::string argv[] = {"", "-h", "--test", "-test"};    
    auto opts = p.parse(argc, argv, non_opts, bad_opts);
    std::vector<std::string> non_opts_answer;
    ASSERT_EQ(non_opts, non_opts_answer);
    std::vector<std::pair<std::string, std::string>> opts_answer = {{"h", ""}};
    ASSERT_EQ(opts, opts_answer);
    std::vector<std::pair<std::string, int>> bad_opts_answer = {{"--test", NO_ARGUMENT}, {"-test", UNDEFINED}};
    ASSERT_EQ(bad_opts, bad_opts_answer);    
}

TEST(OptParserTest, ParsingTest3) {
    non_opts.clear();
    bad_opts.clear();
    int argc = 4;
    std::string argv[] = {"", "-h", "--test", "--xxx"};    
    auto opts = p.parse(argc, argv, non_opts, bad_opts);
    std::vector<std::string> non_opts_answer;
    ASSERT_EQ(non_opts, non_opts_answer);
    std::vector<std::pair<std::string, std::string>> opts_answer = {{"h", ""}};
    ASSERT_EQ(opts, opts_answer);
    std::vector<std::pair<std::string, int>> bad_opts_answer = {{"--test", NO_ARGUMENT}, {"--xxx", UNDEFINED}};
    ASSERT_EQ(bad_opts, bad_opts_answer);    
}

TEST(OptParserTest, ParsingTest4) {
    non_opts.clear();
    bad_opts.clear();
    int argc = 4;
    std::string argv[] = {"", "-h", "--test", "-123"};    
    auto opts = p.parse(argc, argv, non_opts, bad_opts);
    std::vector<std::string> non_opts_answer;
    ASSERT_EQ(non_opts, non_opts_answer);
    std::vector<std::pair<std::string, std::string>> opts_answer = {{"h", ""}, {"test", "-123"}};
    ASSERT_EQ(opts, opts_answer);
    std::vector<std::pair<std::string, int>> bad_opts_answer;
    ASSERT_EQ(bad_opts, bad_opts_answer);    
}

TEST(OptParserTest, ParsingTest5) {
    non_opts.clear();
    bad_opts.clear();
    int argc = 4;
    std::string argv[] = {"", "-h", "--test", "-c"};    
    auto opts = p.parse(argc, argv, non_opts, bad_opts);
    std::vector<std::string> non_opts_answer;
    ASSERT_EQ(non_opts, non_opts_answer);
    std::vector<std::pair<std::string, std::string>> opts_answer = {{"h", ""}, {"c", ""}};
    ASSERT_EQ(opts, opts_answer);
    std::vector<std::pair<std::string, int>> bad_opts_answer = {{"--test", NO_ARGUMENT}};
    ASSERT_EQ(bad_opts, bad_opts_answer);    
}
