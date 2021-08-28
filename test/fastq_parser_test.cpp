#include <gtest/gtest.h>

#include "fastq_parser.cpp"



TEST(FastqParserTest, ParsingTest1) {
    std::string prefix = "../../test_data/";
    FastqParser* reads = new FastqParser();
    reads->Parse(prefix + "test1.fastq");
    ASSERT_EQ(reads->NumSequences(), 2);
    ASSERT_EQ(reads->MinL(), 1);
    ASSERT_EQ(reads->MaxL(), 4);
    ASSERT_EQ(reads->AverageL(), 2.5);
    
    reads->Parse(prefix + "test2.fastq");
    ASSERT_EQ(reads->NumSequences(), 4);
    ASSERT_EQ(reads->MinL(), 1);
    ASSERT_EQ(reads->MaxL(), 7);
    ASSERT_EQ(reads->AverageL(), 3.75);
    
    delete reads;    
    
}

