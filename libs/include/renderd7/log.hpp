#pragma once
#include <fstream>
#include <stdarg.h>
#include <string>
#include <time.h>
#include <unistd.h>

/// @brief Log Class
class Log {
public:
  /// @brief Constructor
  Log();
  /// @brief Deconstructor
  ~Log();
  /// @brief Init the Logger
  /// @param filename Filename[_data_time.log]
  void Init(const char *filename);
  /// @brief Write a String to the File
  /// @param debug_text string
  void Write(std::string debug_text);
  /// @brief Get the Date
  /// @return Date as string fmt[data_time]
  std::string logDate(void);
  /// @brief Format a string like sprintf
  /// @param fmt_str the string wich defines the fmt
  /// @param ... Additional Data
  /// @return Formatted String
  std::string format(const std::string &fmt_str, ...);

private:
  /// \param filename the name of the logfile
  std::string filename;
};
