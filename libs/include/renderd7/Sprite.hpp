#pragma once

#include <citro2d.h>
#include <citro3d.h>

#include <renderd7/Image.hpp>
#include <renderd7/Sheet.hpp>

namespace RenderD7 {
/// Sprite Class
class Sprite {
public:
  /// \brief Construct Sprite
  Sprite();
  /// \brief Deconstruct Sprite
  ~Sprite();
  /// \brief Load a Sprite From SpriteSheet
  /// \param sheet the Sheet to load from.(RenderD7::Sheet)
  /// \param index the number of the Sprite in the Sheet
  void FromSheet(RenderD7::Sheet *sheet, size_t index);
  /// \brief Load a Sprite From SpriteSheet
  /// \param img the Image to load from.(RenderD7::Image)
  void FromImage(RenderD7::Image *img);
  bool Draw();
  void SetCenter(float x, float y);
  void SetPos(float x, float y);
  void SetScale(float x, float y);
  void SetRotation(float rotation);
  void Rotate(float speed);
  float getWidth();
  float getHeigh();
  float getPosX();
  float getPosY();

private:
  C2D_ImageTint tint;
  C2D_Sprite sprite;
};
} // namespace RenderD7