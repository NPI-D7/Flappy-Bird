#pragma once

#include <renderd7/Sheet.hpp>
#include <renderd7/Sprite.hpp>

#include <citro2d.h>
#include <citro3d.h>

namespace RenderD7 {
/// @brief SpriteSheetAnimation Class
class SpriteSheetAnimation : public RenderD7::Sprite {
public:
  /// @brief Constructor
  SpriteSheetAnimation();
  /// @brief Deconstructor
  ~SpriteSheetAnimation();
  /// @brief Setup an Animation
  /// @param sheet Input Spritesheet
  /// @param imagecount Count of Images
  /// @param startimage Where to Start the Loop
  /// @param frame_begin Current Time (Should be 0)
  /// @param frame_finish Time Length
  void Setup(RenderD7::Sheet *sheet, size_t imagecount, size_t startimage,
             float frame_begin, float frame_finish);
  /// @brief Play the Animation
  /// @param timespeed Speed of the animation
  void Play(float timespeed);

private:
  /// @param images Count of Images
  size_t images;
  /// @param imgs Another Count of images ???
  size_t imgs = 0;
  /// @param D_totaltime Current Time
  float D_totaltime;
  /// @param sheet The Sheet of Images
  RenderD7::Sheet *sheet;
  /// @param time Total Time from frame_finish
  float time;
};
} // namespace RenderD7