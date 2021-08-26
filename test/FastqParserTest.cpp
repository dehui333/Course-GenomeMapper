#include <gtest/gtest.h>

#include "FastqParser.cpp"



TEST(FastqParserTest, ParsingTest1) {
    std::string prefix = "../../test_data/";
    FastqParser* reads = new FastqParser();
    reads->parse(prefix + "test1.fastq");
    ASSERT_EQ(reads->num_sequences(), 2);
    ASSERT_EQ(reads->min_L, 1);
    ASSERT_EQ(reads->max_L, 4);
    ASSERT_EQ(reads->average_L, 2.5);
    
    reads->parse(prefix + "test2.fastq");
    ASSERT_EQ(reads->num_sequences(), 4);
    ASSERT_EQ(reads->min_L, 1);
    ASSERT_EQ(reads->max_L, 7);
    ASSERT_EQ(reads->average_L, 3.75);
    
    delete reads;    
    
}

