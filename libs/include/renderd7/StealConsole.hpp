#pragma once
#include <sstream>
#include <string>

namespace RenderD7 {
class StealConsole {
public:
  StealConsole();
  ~StealConsole();
  std::string GetStdout();

private:
  std::stringstream stolen_stdout;
};
} // namespace RenderD7