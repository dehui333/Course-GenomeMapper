enable_testing()
# directory to get the header files to include
include_directories(PUBLIC "../include/opt_parser")
include_directories(PUBLIC "../include/biosequence_parser")


add_executable(
  opt_parser_test
  opt_parser_test.cpp
)

target_link_libraries(
  opt_parser_test
  gtest_main
)

add_executable(
  fasta_parser_test
  fasta_parser_test.cpp
)

target_link_libraries(
  fasta_parser_test
  gtest_main
)

add_executable(
  fastq_parser_test
  fastq_parser_test.cpp
)

target_link_libraries(
  fastq_parser_test
  gtest_main
)





include(GoogleTest)
gtest_discover_tests(opt_parser_test)
gtest_discover_tests(fasta_parser_test)
gtest_discover_tests(fastq_parser_test)
