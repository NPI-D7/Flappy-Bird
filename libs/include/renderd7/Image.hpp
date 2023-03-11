#pragma once
#include <citro2d.h>
#include <citro3d.h>
#include <memory>

#include <renderd7/Sheet.hpp>
#include <renderd7/bmp.hpp>
#include <renderd7/bmpconverter.hpp>

#include <cassert>
#include <cstring>
#include <renderd7/Color.hpp>
#include <renderd7/external/lodepng.h>

namespace RenderD7 {
/// Image Class
class Image {
public:
  Image() {}
  ~Image();

  void Unload();
  /// Load Image from Png
  /// \param path path to png file
  void LoadPng(const std::string path);
  /// Load the Image from buffer
  /// \param buffer the frame buffer
  void LoadPFromBuffer(const std::vector<u8> &buffer);
  void LoadFromBitmap(BMP bitmap);
  void LoadJpg(std::string path);
  void LoadPixels(int w, int h, int bpp, void *buffer);
  /// Draw the Image directly
  /// \param x The x position
  /// \param y the y position
  /// \param scaleX x scale from 0.0 to 1.0
  /// \param scaleY y scale from 0.0 to 1.0
  bool Draw(float x, float y, float scaleX = 1.0f, float scaleY = 1.0f);
  /// \brief Get The Image
  /// \return C2D_Image
  C2D_Image Get() { return this->img; }

  void FromSheet(RenderD7::Sheet sheet, size_t index);
  /// \param img this is the C2D_Image
  C2D_Image img;
  /// \param loadet whether the image is loadet or not
  bool loadet = false;
};
} // namespace RenderD7