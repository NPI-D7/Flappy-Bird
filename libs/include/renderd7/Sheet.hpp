#pragma once
#include <citro2d.h>
#include <citro3d.h>

namespace RenderD7 {
/** The Spritesheet Class */
class Sheet {
public:
  /// Construct sheet
  Sheet();
  // Deconstruct sheet
  ~Sheet();
  /// Load a Sritesheet
  /// \param path Path to the Spritesheet (.t3x)
  Result Load(const char *path);
  /// Unload the Spritesheet
  void Free();
  /// The Spritesheet
  C2D_SpriteSheet spritesheet;
};
} // namespace RenderD7