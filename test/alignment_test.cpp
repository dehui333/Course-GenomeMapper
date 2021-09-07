#include <gtest/gtest.h>

#include "align.cpp"



TEST(GlobalAlignmentTest, AllMatch) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar = "";
    unsigned int target_begin = -1;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::KGlobal,1, -1, -1,  num_match, num_mismatch, num_ins, num_del,&cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Delete) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::KGlobal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Insert) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::KGlobal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "1=1I2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, Mismatch) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::KGlobal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "3=1X");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, DelAndInsAtEnds) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::KGlobal, 1, -1, -1, num_match, num_mismatch, num_ins, num_del,&cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2I2=2D");
    ASSERT_EQ(target_begin, 0);
}

TEST(GlobalAlignmentTest, MismatchAtEnds) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::KGlobal, 1, -1, -1, num_match, num_mismatch, num_ins, num_del,&cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2X2=2X");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, AllMatch) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar = "";
    unsigned int target_begin = -1;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::KLocal,1, -1, -1,  num_match, num_mismatch, num_ins, num_del,&cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, Delete) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::KLocal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, Insert) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::KLocal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2S2=");
    ASSERT_EQ(target_begin, 1);
}

TEST(LocalAlignmentTest, Mismatch) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::KLocal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "3=1S");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, DelAndInsAtEnds) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::KLocal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2S2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(LocalAlignmentTest, MismatchAtEnds) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::KLocal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2S2=2S");
    ASSERT_EQ(target_begin, 2);
}

TEST(SemiGlobalAlignmentTest, AllMatch) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar = "";
    unsigned int target_begin = -1;
    int score = mist::Align("ATCG", 4, "ATCG", 4, AlignmentType::KSemiGlobal,1, -1, -1, num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 4);
    ASSERT_EQ(cigar, "4=");
    ASSERT_EQ(target_begin, 0);
}


TEST(SemiGlobalAlignmentTest, Delete) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATTCG", 5, AlignmentType::KSemiGlobal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 3);
    ASSERT_EQ(cigar, "2=1D2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, Insert) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ACG", 3, AlignmentType::KSemiGlobal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "1=1I2=");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, Mismatch) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "ATCC", 4, AlignmentType::KSemiGlobal, 1, -1, -1,num_match, num_mismatch, num_ins, num_del, &cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "3=1X");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, DelAndInsAtEnds) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("ATCG", 4, "CGAA", 4, AlignmentType::KSemiGlobal, 1, -1, -1, num_match, num_mismatch, num_ins, num_del,&cigar, &target_begin);
    ASSERT_EQ(score , 2);
    ASSERT_EQ(cigar, "2I2=2D");
    ASSERT_EQ(target_begin, 0);
}

TEST(SemiGlobalAlignmentTest, MismatchAtEnds) {
    unsigned int num_match = 0;
    unsigned int num_mismatch = 0;
    unsigned int num_ins = 0;
    unsigned int num_del = 0;
    std::string cigar;
    unsigned int target_begin;
    int score = mist::Align("TTCGTT", 6, "AACGAA", 6, AlignmentType::KSemiGlobal, 1, -1, -1, num_match, num_mismatch, num_ins, num_del,&cigar, &target_begin);
    ASSERT_EQ(score , -2);
    ASSERT_EQ(cigar, "2X2=2X");
    ASSERT_EQ(target_begin, 0);
}






