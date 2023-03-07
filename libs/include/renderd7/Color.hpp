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
struct rgba {
  uint8_t r, g, b, a;
};
class RGBA {
public:
  RGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
      : m_r(r), m_g(g), m_b(b), m_a(a) {}
  uint32_t toRGBA() const {
    return (m_r << 24) | (m_g << 16) | (m_b << 8) | m_a;
  }

  uint8_t m_r, m_g, m_b, m_a;
};
std::string RGB2Hex(int r, int g, int b);
uint32_t Hex(const std::string &color, uint8_t a = 255);
} // namespace Color
} // namespace RenderD7