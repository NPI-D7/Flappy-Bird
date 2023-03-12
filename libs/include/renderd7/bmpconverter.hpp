#pragma once
#include <renderd7/external/lodepng.h>

#include <iostream>

namespace BitmapConverter {
/// returns 0 if all went ok, non-0 if error
/// output image is always given in RGBA (with alpha channel), even if it's a
/// BMP without alpha channel
unsigned decodeBMP(std::vector<unsigned char> &image, unsigned &w, unsigned &h,
                   const std::vector<unsigned char> &bmp);

/// @brief Convert A File
/// @param filename
/// @return data
std::vector<unsigned char> ConvertFile(std::string filename);
/// @brief Convert data
/// @param data
/// @return data
std::vector<unsigned char> ConvertData(std::vector<unsigned char> data);
} // namespace BitmapConverter