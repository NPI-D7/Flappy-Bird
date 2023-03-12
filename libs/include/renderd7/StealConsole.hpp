#pragma once
#include <sstream>
#include <string>

namespace RenderD7 {
/// @brief StealConsole Class
class StealConsole {
public:
  /// @brief Constructor
  StealConsole();
  /// @brief Deconstructor
  ~StealConsole();
  /// @brief The Stolen Stdout
  /// @return Stdout as string
  std::string GetStdout();

private:
  /// @param stolen_stdout Stolen Stdout
  std::stringstream stolen_stdout;
};
} // namespace RenderD7