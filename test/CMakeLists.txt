enable_testing()
# directory to get the header files to include
include_directories(PRIVATE "../include/opt_parser")
include_directories(PRIVATE "../include/biosequence_parser")
include_directories(PRIVATE "../include/mist_alignment_engine")
include_directories(PRIVATE "../include/mist_minimizer_engine")

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

add_executable(
  alignment_test
  alignment_test.cpp
)

target_link_libraries(
  alignment_test
  gtest_main
)

add_executable(
  minimizer_test
  minimizer_test.cpp
)

target_link_libraries(
  minimizer_test
  gtest_main
)







include(GoogleTest)
gtest_discover_tests(opt_parser_test)
gtest_discover_tests(fasta_parser_test)
gtest_discover_tests(fastq_parser_test)
gtest_discover_tests(alignment_test)
gtest_discover_tests(minimizer_test)
