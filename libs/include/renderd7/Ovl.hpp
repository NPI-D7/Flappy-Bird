#pragma once
#include <memory>

namespace RenderD7 {
class Ovl {
public:
  virtual ~Ovl() {}
  virtual void Draw() const = 0;
  virtual void Logic() = 0;
  inline bool IsKilled() { return this->iskilled; }
  inline void Kill() { iskilled = true; }

private:
  bool iskilled = false;
};
void AddOvl(std::unique_ptr<RenderD7::Ovl> scene);
} // namespace RenderD7