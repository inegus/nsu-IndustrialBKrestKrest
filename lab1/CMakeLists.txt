cmake_minimum_required(VERSION 3.20)
project(compressor_project CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include(GNUInstallDirs)
enable_testing()

find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_EXTRACT_ALL YES)
    doxygen_add_docs(docs libcompressor/include)
endif()

add_subdirectory(libcompressor)
add_subdirectory(compressor)
