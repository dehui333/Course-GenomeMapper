#include <gtest/gtest.h>

#include "fasta_parser.cpp"



TEST(FastaParserTest, ParsingTest1) {
    std::string prefix = "../../test_data/";
    FastaParser* reads = new FastaParser();
    reads->Parse(prefix + "test1.fasta");
    ASSERT_EQ(reads->NumSequences(), 2);
    ASSERT_EQ(reads->MinL(), 1);
    ASSERT_EQ(reads->MaxL(), 4);
    ASSERT_EQ(reads->AverageL(), 2.5);
    
    reads->Parse(prefix + "test2.fasta");
    ASSERT_EQ(reads->NumSequences(), 4);
    ASSERT_EQ(reads->MinL(), 1);
    ASSERT_EQ(reads->MaxL(), 7);
    ASSERT_EQ(reads->AverageL(), 3.75);
    
    delete reads;    
    
}

