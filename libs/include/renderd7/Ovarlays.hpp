#pragma once

#include <renderd7/Ovl.hpp>

namespace RenderD7 {
class Ovl_Ftrace : public RenderD7::Ovl {
  /// @brief Constructor
  Ovl_Ftrace();
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
};
class Ovl_UiBattery : public RenderD7::Ovl {
  /// @brief Constructor
  /// @param percentage Percentage
  Ovl_UiBattery(float *percentage);
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
  float *_pct_addr = 0;
};
class Ovl_UiSound : public RenderD7::Ovl {
  /// @brief Constructor
  /// @param percentage Percentage
  Ovl_UiSound(float *percentage);
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
  float *_pct_addr = 0;
};
class Ovl_Ui3d : public RenderD7::Ovl {
  /// @brief Constructor
  /// @param percentage Percentage
  Ovl_Ui3d(float *percentage);
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
  float *_pct_addr = 0;
};
class Ovl_UiWifi : public RenderD7::Ovl {
  /// @brief Constructor
  /// @param level strengh level
  Ovl_UiWifi(uint8_t *level);
  /// @brief Override for Draw
  void Draw(void) const override;
  /// @brief Override for Logic
  void Logic() override;

private:
  uint8_t *_pct_addr = 0;
};
} // namespace RenderD7