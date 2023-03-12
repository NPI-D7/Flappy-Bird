#pragma once

#include <citro2d.h>
#include <citro3d.h>

#include <renderd7/Image.hpp>
#include <renderd7/Sheet.hpp>

namespace RenderD7 {
/// @brief Sprite Class
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
  /// @brief Draw the Sprite
  /// @return success ?
  bool Draw();
  /// @brief Set the Center Position
  /// @param x X Pos
  /// @param y Y Pos
  void SetCenter(float x, float y);
  /// @brief Set the Sprite's Position
  /// @param x X Pos
  /// @param y Y Pos
  void SetPos(float x, float y);
  /// @brief Set The Sprite's Scale
  /// @param x Scale on X-Axis
  /// @param y Scale on Y-Axis
  void SetScale(float x, float y);
  /// @brief Set the Sprite's Rotation
  /// @param rotation ratation
  void SetRotation(float rotation);
  /// @brief Rotate the Sprite
  /// @param speed Speed to Rotate
  void Rotate(float speed);
  /// @brief Get Tje Sprite's Width
  /// @return Width
  float getWidth();
  /// @brief Get the Sprite's Height
  /// @return Height
  float getHeight();
  /// @brief Get The Sprite's X Position
  /// @return X Position
  float getPosX();
  /// @brief Get the Sprite's Y Position
  /// @return Y Position
  float getPosY();

private:
  /// @param tint ImageTint (unused)
  C2D_ImageTint tint;
  /// @param sprite The Sprite
  C2D_Sprite sprite;
};
} // namespace RenderD7