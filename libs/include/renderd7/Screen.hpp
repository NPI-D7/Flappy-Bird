#pragma once
#include <citro2d.h>
#include <citro3d.h>

extern C3D_RenderTarget *Top;
extern C3D_RenderTarget *TopRight;
extern C3D_RenderTarget *Bottom;

namespace RenderD7 {
/// Set current RenderScreen
/// \param target The RenderTarget Top, Bottom
void OnScreen(C3D_RenderTarget *target);
} // namespace RenderD7
