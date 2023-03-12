#pragma once
#include <citro2d.h>
#include <citro3d.h>

/// \param Top Tob-Screen Target
extern C3D_RenderTarget *Top;
/// \param TopRight Top-Right-Screen Target (Never atually used)
extern C3D_RenderTarget *TopRight;
/// \param Bottom Bottom-Screen Target
extern C3D_RenderTarget *Bottom;

namespace RenderD7 {
/// @brief Begin Drawing On Specific Screen
/// @param target The Screen Target (Top, Bottom or TopTight)
void OnScreen(C3D_RenderTarget *target);
} // namespace RenderD7
