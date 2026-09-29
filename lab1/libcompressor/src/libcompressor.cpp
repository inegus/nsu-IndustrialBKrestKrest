#include "libcompressor.hpp"

#include <bzlib.h>
#include <zlib.h>

#include <cstring>

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input)
{
    libcompressor_Buffer output;
    output.data = nullptr;
    output.size = 0;

    if (input.data == nullptr || input.size <= 0)
        {
            return output;
        }

    int out_size = input.size + 1024;
    char *out_data = static_cast<char *>(std::malloc(out_size));
    if (!out_data)
        {
            return output;
        }
    if (algo == libcompressor_CompressionAlgorithm::libcompressor_Zlib)
        {
            uLongf destLen = out_size;
            int ret = compress2(reinterpret_cast<Bytef *>(out_data), &destLen,
                                reinterpret_cast<const Bytef *>(input.data), input.size, Z_DEFAULT_COMPRESSION);
            if (ret == Z_OK)
                {
                    output.data = out_data;
                    output.size = static_cast<int>(destLen);
                }
            else
                {
                    std::free(out_data);
                }
        }
    else if (algo == libcompressor_CompressionAlgorithm::libcompressor_Bzip)
        {
            unsigned int destLen = out_size;
            int ret = BZ2_bzBuffToBuffCompress(out_data, &destLen, input.data, input.size, 1, 0, 0);
            if (ret == BZ_OK)
                {
                    output.data = out_data;
                    output.size = static_cast<int>(destLen);
                }
            else
                {
                    std::free(out_data);
                }
        }
    else
        {
            std::free(out_data);
        }

    return output;
}