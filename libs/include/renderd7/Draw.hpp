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
/// @brief Draw a Centered Text
/// @param x Pos X
/// @param y Pos Y
/// @param size Scale of the Text
/// @param color Color of The Text
/// @param Text Striing to Display
/// @param maxWidth Width to Calculate Centered Pos
/// @param maxHeight Height to Calculate Centered Pos
/// @param fnt Custom Font
void TextCentered(float x, float y, float size, u32 color, std::string Text,
                  int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
/// @brief Draw a Text
/// @param x Pos X
/// @param y Pos Y
/// @param size Scale of the Text
/// @param color Color of The Text
/// @param Text Striing to Display
/// @param maxWidth Width to Calculate Centered Pos
/// @param maxHeight Height to Calculate Centered Pos
/// @param fnt Custom Font
void Text(float x, float y, float size, u32 color, std::string Text,
          int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
/// @brief Draw a Text Set to the Right
/// @param x Pos X
/// @param y Pos Y
/// @param size Scale of the Text
/// @param color Color of The Text
/// @param Text Striing to Display
/// @param maxWidth Width to Calculate Centered Pos
/// @param maxHeight Height to Calculate Centered Pos
/// @param fnt Custom Font
void TextRight(float x, float y, float size, u32 color, std::string Text,
               int maxWidth = 0, int maxHeight = 0, C2D_Font fnt = nullptr);
/// @brief Get Width of Text
/// @param size Size of the Text
/// @param Text String of The text
/// @param fnt Custom Font
/// @return The Size
float GetTextWidth(float size, std::string Text, C2D_Font fnt = nullptr);
/// @brief Get Text Size
/// @param size Size of The Text
/// @param width Width of the Text
/// @param height Height of The Text
/// @param Text String of Text
/// @param fnt Custom Font
void GetTextSize(float size, float *width, float *height, std::string Text,
                 C2D_Font fnt = nullptr);
/// @brief Get Height of the Text
/// @param size Size of the Text
/// @param Text String of the Text
/// @param fnt Custom Font
/// @return The Height
float GetTextHeight(float size, std::string Text, C2D_Font fnt = nullptr);
/// @brief Load A .bcfnt
/// @param fnt Output Font
/// @param Path path of The File
/// @return Result Code
Result LoadFont(C2D_Font &fnt, const char *Path = "");
/// @brief Unload a Font
/// @param fnt Font to Unload
/// @return Result Code
Result UnloadFont(C2D_Font &fnt);
/// @brief Draw a Circle
/// @param x Pos X
/// @param y Pos Y
/// @param radius Radius of the Circle
/// @param color Color of the circle
/// @return success ?
bool Circle(float x, float y, float radius, u32 color);
/// @brief Draw A Citro2D Image
/// @param img Image to Draw
/// @param x Pos X
/// @param y Pos Y
/// @param scaleX Scale of X-Axis
/// @param scaleY Scale of Y-Axis
/// @return success ?
bool Image(C2D_Image img, float x, float y, float scaleX = 1.0f,
           float scaleY = 1.0f);
} // namespace Draw
} // namespace RenderD7