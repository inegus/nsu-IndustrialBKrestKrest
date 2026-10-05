add_executable(libcompressortest libcompressortest.cpp)

target_link_libraries(libcompressortest PRIVATE libcompressor GTest::gtest GTest::gtest_main)

enable_testing()

include(GoogleTest)
gtest_discover_tests(libcompressortest
    DISCOVERY_TIMEOUT 10
    XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/results
)