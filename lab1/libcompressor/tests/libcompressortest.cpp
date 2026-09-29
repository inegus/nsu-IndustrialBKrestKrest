#include <gtest/gtest.h>

#include <cstdlib>

#include "libcompressor.hpp"

constexpr int SIZE = 9;

TEST(LibcompressorTest, ZlibNonEmpty)
{
    const char *input_data = "data";
    libcompressor_Buffer input{const_cast<char *>(input_data), SIZE};
    libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, input);
    EXPECT_NE(output.data, nullptr);
    EXPECT_GT(output.size, 0);
    if (output.data) std::free(output.data);
}

TEST(LibcompressorTest, BzipNonEmpty)
{
    const char *input_data = "data";
    libcompressor_Buffer input{const_cast<char *>(input_data), SIZE};
    libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Bzip, input);
    EXPECT_NE(output.data, nullptr);
    EXPECT_GT(output.size, 0);
    if (output.data) std::free(output.data);
}

TEST(LibcompressorTest, ZlibEmpty)
{
    libcompressor_Buffer input{nullptr, 0};
    libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, input);
    EXPECT_EQ(output.data, nullptr);
    EXPECT_EQ(output.size, 0);
}

TEST(LibcompressorTest, BzipEmpty)
{
    libcompressor_Buffer input{nullptr, 0};
    libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Bzip, input);
    EXPECT_EQ(output.data, nullptr);
    EXPECT_EQ(output.size, 0);
}
