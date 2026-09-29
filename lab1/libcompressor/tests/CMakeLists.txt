add_executable(libcompressortest libcompressortest.cpp)
target_link_libraries(libcompressortest PRIVATE libcompressor GTest::gtest GTest::gtest_main)

target_compile_options(libcompressortest PRIVATE -Wall -Wextra -Wpedantic -Werror)

include(GoogleTest)
gtest_discover_tests(libcompressortest)

add_test(NAME libcompressortest COMMAND libcompressortest --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results.xml)
