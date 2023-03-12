#pragma once
#include <renderd7/BitmapPrinter.hpp>
#include <renderd7/Color.hpp>
#include <renderd7/Image.hpp>
#include <renderd7/Ovl.hpp>
#include <renderd7/Screen.hpp>

namespace RenderD7 {
/// @brief Toast Class
class Toast : public RenderD7::Ovl {
public:
  /// @brief Constructor
  /// @param head Displayed String in Head
  /// @param msg Displayed String in Message Box
  Toast(std::string head, std::string msg);
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
  /// @param head The Header Text
  /// @param nsg The Message-Box Text
  std::string head, msg;
  /// @param msgposy Position Y of The Toast
  int msgposy = 240;
  /// @param delay Delay of the Toast
  int delay = 0;
};
} // namespace RenderD7