#include <gtest/gtest.h>

#include <cstdlib>

#include "libcompressor.hpp"

constexpr int SIZE = 4;

TEST(LibcompressorTest1, ZlibNonEmpty)
{
  const char* input_data = "data";
  libcompressor_Buffer input{(char*)(input_data), SIZE};
  libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, input);
  EXPECT_NE(output.data, nullptr);
  EXPECT_GT(output.size, 0);
  if (output.data != nullptr) {
    std::free(output.data);
  }
}

TEST(LibcompressorTest2, BzipNonEmpty)
{
  const char* input_data = "data";
  libcompressor_Buffer input{(char*)(input_data), SIZE};
  libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Bzip, input);
  EXPECT_NE(output.data, nullptr);
  EXPECT_GT(output.size, 0);
  if (output.data != nullptr) {
    std::free(output.data);
  }
}

TEST(LibcompressorTest3, ZlibEmpty)
{
  libcompressor_Buffer input{nullptr, 0};
  libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, input);
  EXPECT_EQ(output.data, nullptr);
  EXPECT_EQ(output.size, 0);
}

TEST(LibcompressorTest4, BzipEmpty)
{
  libcompressor_Buffer input{nullptr, 0};
  libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Bzip, input);
  EXPECT_EQ(output.data, nullptr);
  EXPECT_EQ(output.size, 0);
}

TEST(LibcompressorTest5, ZlibTestString)
{
  const char* input_data = "test_string";
  unsigned char expected[] = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89, 0x2f, 0x2e, 0x29,
                              0xca, 0xcc, 0x4b, 0x07, 0x00, 0x1c, 0x79, 0x04, 0xb7};
  libcompressor_Buffer input = {(char*)input_data, 11};
  libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Zlib, input);
  ASSERT_NE(output.data, nullptr);
  ASSERT_EQ(output.size, 19);
  for (int i = 0; i < output.size; ++i) {
    EXPECT_EQ((unsigned char)output.data[i], expected[i]);
  }
  free(output.data);
}

TEST(LibcompressorTest6, BzipTestString)
{
  const char* input_data = "test_string";
  unsigned char expected[] = {0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
                              0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
                              0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
                              0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0};
  libcompressor_Buffer input = {(char*)input_data, 11};
  libcompressor_Buffer output = libcompressor_compress(libcompressor_CompressionAlgorithm::libcompressor_Bzip, input);
  ASSERT_NE(output.data, nullptr);
  ASSERT_EQ(output.size, 48);
  for (int i = 0; i < output.size; ++i) {
    EXPECT_EQ((unsigned char)output.data[i], expected[i]);
  }
  free(output.data);
}