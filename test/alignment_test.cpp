#include <gtest/gtest.h>

#include "align.cpp"



TEST(GlobalAlignmentTest, AllMatch) {
    std::string cigar = "";
    unsigned int target_begin = -1;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::KGlobal,1, -1, -1,  &cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Delete) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::KGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Insert) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::KGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "1=1I2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Mismatch) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::KGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "3=1X");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, DelAndInsAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::KGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2I2=2D");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, MismatchAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::KGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2X2=2X");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, AllMatch) {
    std::string cigar = "";
    unsigned int target_begin = -1;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::KLocal,1, -1, -1,  &cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, Delete) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::KLocal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, Insert) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::KLocal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2S2=");
    ASSERT_EQ(target_begin, 1);
}

TEST(LocalAlignmentTest, Mismatch) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::KLocal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "3=1S");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, DelAndInsAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::KLocal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2S2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, MismatchAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::KLocal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2S2=2S");
    ASSERT_EQ(target_begin, 2);
}

TEST(SemiGlobalAlignmentTest, AllMatch) {
    std::string cigar = "";
    unsigned int target_begin = -1;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::KSemiGlobal,1, -1, -1,  &cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}


TEST(SemiGlobalAlignmentTest, Delete) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::KSemiGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, Insert) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::KSemiGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "1=1I2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, Mismatch) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::KSemiGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "3=1X");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, DelAndInsAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::KSemiGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2I2=2D");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, MismatchAtEnds) {
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::KSemiGlobal, 1, -1, -1, &cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2X2=2X");
    ASSERT_EQ(target_begin, 0);
}






