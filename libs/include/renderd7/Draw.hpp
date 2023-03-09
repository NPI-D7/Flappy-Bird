#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <string>

namespace RenderD7 {
namespace Draw {
/// @brief Draw Rectangle
/// @param x Pos X
/// @param y Pos Y
/// @param w Width
/// @param h Height
/// @param color Color
/// @return success ?
bool Rect(float x, float y, float w, float h, u32 color);
/// @brief Draw a not filled Rectangle
/// @param p1x Pos X
/// @param p1y Pos Y
/// @param w Width
/// @param h Height
/// @param color Color
/// @param scale Scale
/// @return success ?
bool NFRect(float p1x, float p1y, float w, float h, u32 color, float scale = 1);
/// @brief Draw A Pixel
/// @param x Pos X
/// @param y Pos Y
/// @param color Color
/// @return success ?
bool Px(float x, float y, u32 color);
void TextCentered(float x, float y, float size, u32 color, std::string Text,
                  int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
void Text(float x, float y, float size, u32 color, std::string Text,
          int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
void TextRight(float x, float y, float size, u32 color, std::string Text,
               int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
float GetTextWidth(float size, std::string Text, C2D_Font fnt = nullptr);
void GetTextSize(float size, float *width, float *height, std::string Text,
                 C2D_Font fnt = nullptr);
float GetTextHeight(float size, std::string Text, C2D_Font fnt = nullptr);
Result LoadFont(C2D_Font &fnt, const char *Path = "");
Result UnloadFont(C2D_Font &fnt);
bool Circle(float x, float y, float radius, u32 color);
bool Image(C2D_Image img, float x, float y, float scaleX = 1.0f,
           float scaleY = 1.0f);
} // namespace Draw
} // namespace RenderD7