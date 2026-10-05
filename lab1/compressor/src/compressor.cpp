#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "libcompressor.hpp"

int main(int argc, char* argv[])
{
  spdlog::set_default_logger(spdlog::stderr_color_mt("stderr"));

  if (argc < 3) {
    spdlog::error("Not enough arguments");
    return EXIT_FAILURE;
  }

  std::string algo_str = argv[1];
  std::string input_str = argv[2];

  libcompressor_CompressionAlgorithm algo = libcompressor_CompressionAlgorithm::None;
  if (algo_str == "zlib") {
    algo = libcompressor_CompressionAlgorithm::libcompressor_Zlib;
  } else if (algo_str == "bzip") {
    algo = libcompressor_CompressionAlgorithm::libcompressor_Bzip;
  } else {
    spdlog::error("unsupported algo");
    return EXIT_FAILURE;
  }

  libcompressor_Buffer input{};
  input.data = (char*)input_str.c_str();
  input.size = (int)input_str.length();

  libcompressor_Buffer output = libcompressor_compress(algo, input);

  if (output.data == nullptr && output.size == 0) {
    spdlog::error("Compression failed");
    return EXIT_FAILURE;
  }
  for (int i = 0; i < output.size; i++) {
    std::cout << output.data[i] << " ";
  }

  free(output.data);

  return EXIT_SUCCESS;
}