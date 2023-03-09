#pragma once
#include <cstring>
#include <functional>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <unistd.h>

#define UNPACK_RGBA(col) (uint8_t)(col >> 24), (col >> 16), (col >> 8), (col)
#define UNPACK_BGRA(col) (uint8_t)(col >> 8), (col >> 16), (col >> 24), (col)

namespace RenderD7 {
namespace Color {
/// @brief RGBA Struct
struct rgba {
  /// @brief rgba Colors
  uint8_t r, g, b, a;
};
/// @brief RGBA Class
class RGBA {
public:
  /// @brief Construct
  /// @param r
  /// @param g
  /// @param b
  /// @param a
  RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
      : m_r(r), m_g(g), m_b(b), m_a(a) {}
  /// @brief Get as Uint32
  /// @return color
  uint32_t toRGBA() const {
    return (m_r << 24) | (m_g << 16) | (m_b << 8) | m_a;
  }

  uint8_t m_r, m_g, m_b, m_a;
};
/// @brief Convert RGB to Hex
/// @param r
/// @param g
/// @param b
/// @return Hex-String
std::string RGB2Hex(int r, int g, int b);
/// @brief Hex to U32
/// @param color
/// @param a
/// @return Color32
uint32_t Hex(const std::string &color, uint8_t a = 255);
} // namespace Color
} // namespace RenderD7