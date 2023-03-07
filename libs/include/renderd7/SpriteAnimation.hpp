#pragma once

#include <renderd7/Sheet.hpp>
#include <renderd7/Sprite.hpp>

#include <citro2d.h>
#include <citro3d.h>

namespace RenderD7 {
class SpriteSheetAnimation : public RenderD7::Sprite {
public:
  SpriteSheetAnimation();
  ~SpriteSheetAnimation();
  void Setup(RenderD7::Sheet *sheet, size_t imagecount, size_t startimage,
             float frame_begin, float frame_finish);
  void Play(float timespeed);

private:
  size_t images;
  size_t imgs = 0;
  float D_totaltime;
  RenderD7::Sheet *sheet;
  float time;
};
} // namespace RenderD7