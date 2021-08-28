enable_testing()
# directory to get the header files to include
include_directories(PUBLIC "../include/opt_Parser")
include_directories(PUBLIC "../include/bio_sequence_parser")


add_executable(
  OptParserTest
  opt_parser_test.cpp
)

target_link_libraries(
  OptParserTest
  gtest_main
)

add_executable(
  FastaParserTest
  fasta_parser_test.cpp
)

target_link_libraries(
  FastaParserTest
  gtest_main
)

add_executable(
  FastqParserTest
  fastq_parser_test.cpp
)

target_link_libraries(
  FastqParserTest
  gtest_main
)





include(GoogleTest)
gtest_discover_tests(OptParserTest)
gtest_discover_tests(FastaParserTest)
gtest_discover_tests(FastqParserTest)
