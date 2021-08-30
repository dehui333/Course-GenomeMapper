#include <gtest/gtest.h>

#include "align.cpp"



TEST(GlobalAlignmentTest, AllMatch) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::global, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Delete) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::global, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Insert) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::global, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "1=1I2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, NotMatch) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::global, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "3=1X");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, DelAndInsAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::global, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2I2=2D");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, NotMatchAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::global, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2X2=2X");
    ASSERT_EQ(target_begin, 0);
}








