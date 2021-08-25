enable_testing()
# directory to get the header files to include
include_directories(PUBLIC "../include/OptParser")
include_directories(PUBLIC "../include/FastaParser")


add_executable(
  OptParserTest
  OptParserTest.cpp
)

target_link_libraries(
  OptParserTest
  gtest_main
)

add_executable(
  FastaParserTest
  FastaParserTest.cpp
)

target_link_libraries(
  FastaParserTest
  gtest_main
)




include(GoogleTest)
gtest_discover_tests(OptParserTest)
gtest_discover_tests(FastaParserTest)
