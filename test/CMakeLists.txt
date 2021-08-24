enable_testing()
# directory to get the header files to include
include_directories(PUBLIC "../include/OptParser")


add_executable(
  OptParserTest
  OptParserTest.cpp
)
target_link_libraries(
  OptParserTest
  gtest_main
)




include(GoogleTest)
gtest_discover_tests(OptParserTest)
