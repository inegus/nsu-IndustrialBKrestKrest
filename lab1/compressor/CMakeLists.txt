add_executable(compressor src/compressor.cpp)

target_link_libraries(compressor PRIVATE libcompressor spdlog::spdlog)

install(TARGETS compressor DESTINATION ${CMAKE_INSTALL_BINDIR})