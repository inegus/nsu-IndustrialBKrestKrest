add_executable(compressor src/compressor.cpp)
target_link_libraries(compressor PRIVATE libcompressor spdlog::spdlog)

target_compile_options(compressor PRIVATE -Wall -Wextra -Wpedantic -Werror)

install(TARGETS compressor RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})