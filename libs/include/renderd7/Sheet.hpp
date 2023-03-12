#pragma once
#include <citro2d.h>
#include <citro3d.h>

namespace RenderD7 {
/// @brief SpriteSheet Class
class Sheet {
public:
  /// @brief Constructor
  Sheet();
  /// @brief Deconstructor
  ~Sheet();
  /// @brief Load A Spritesheet File
  /// @param path Path to the t3x
  /// @return Result Code
  Result Load(const char *path);
  /// @brief Unload the Sheet
  void Free();
  /// \param spritesheet The Sheet
  C2D_SpriteSheet spritesheet;
};
} // namespace RenderD7