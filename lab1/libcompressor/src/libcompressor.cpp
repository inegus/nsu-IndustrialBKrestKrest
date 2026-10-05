#include "libcompressor.hpp"

#include <bzlib.h>
#include <zlib.h>

#include <cstdlib>

#define MAX_OUT 1024

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input)
{
  libcompressor_Buffer output = {nullptr, 0};

  if (input.data == nullptr || input.size <= 0) {
    return output;
  }

  int out_size = input.size + MAX_OUT;
  char* out_data = (char*)malloc(out_size);
  if (out_data == nullptr) {
    return output;
  }

  if (algo == libcompressor_CompressionAlgorithm::libcompressor_Zlib) {
    uLongf destLen = out_size;
    int ret = compress2((Bytef*)out_data, &destLen, (const Bytef*)input.data, input.size, Z_DEFAULT_COMPRESSION);
    if (ret == Z_OK) {
      output.data = out_data;
      output.size = (int)destLen;
    } else {
      free(out_data);
    }
  } else if (algo == libcompressor_CompressionAlgorithm::libcompressor_Bzip) {
    unsigned int destLen = out_size;
    int ret = BZ2_bzBuffToBuffCompress(out_data, &destLen, input.data, input.size, 1, 0, 0);
    if (ret == BZ_OK) {
      output.data = out_data;
      output.size = (int)destLen;
    } else {
      free(out_data);
    }
  } else {
    free(out_data);
  }

  return output;
}