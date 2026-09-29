#pragma once

#include <atomic>
#include <cstdlib>

enum class libcompressor_CompressionAlgorithm : std::uint8_t
{
    libcompressor_Zlib,
    libcompressor_Bzip
};

struct libcompressor_Buffer
{
    char *data;
    int size;
};

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);