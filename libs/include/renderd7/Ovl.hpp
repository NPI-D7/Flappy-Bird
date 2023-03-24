#pragma once
#include <memory>

namespace RenderD7 {
/// @brief The Overlay Class (Used for Toasts for example)
class Ovl {
public:
  /// @brief Deconstructor
  virtual ~Ovl() {}
  /// @brief Function Called to Draw this
  virtual void Draw() const = 0;
  /// @brief Logic of the Overlay
  virtual void Logic() = 0;
  /// @brief Should the overlay be killed
  /// @return Killed or Not
  inline bool IsKilled() { return this->iskilled; }
  /// @brief Kill The Overlay
  inline void Kill() { iskilled = true; }

private:
  /// @param iskilled For IsKilled();
  bool iskilled = false;
};
/// @brief Add an Overlay to the Screen
/// @param scene Overlay to push to Screen
void AddOvl(std::unique_ptr<RenderD7::Ovl> scene);
/// @brief Add an Overlay to the Toast Stack
/// @param scene Overlay to push to Toast Stack
void AddToast(std::unique_ptr<RenderD7::Ovl> scene);
} // namespace RenderD7