add_library(libcompressor STATIC src/libcompressor.cpp)

target_include_directories(libcompressor PUBLIC include)

target_link_libraries(libcompressor PUBLIC ZLIB::ZLIB BZip2::BZip2)

install(TARGETS libcompressor DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(tests)