#pragma once
#include <renderd7/BitmapPrinter.hpp>
#include <renderd7/Color.hpp>
#include <renderd7/Image.hpp>
#include <renderd7/Ovl.hpp>
#include <renderd7/Screen.hpp>

namespace RenderD7 {
class Toast : public RenderD7::Ovl {
public:
  Toast(std::string head, std::string msg);
  void Draw(void) const override;
  void Logic() override;

private:
  RenderD7::BitmapPrinter toast = RenderD7::BitmapPrinter(400, 70);
  RenderD7::Image *toastrendered;
  std::string head, msg;
  int msgposy = 240;
  int delay = 0;
};
} // namespace RenderD7