#pragma once
#include <fstream>
#include <stdarg.h>
#include <string>
#include <time.h>
#include <unistd.h>

/** Log Class */
class Log {
public:
  /** Construct */
  Log();
  /** Deconstruct */
  ~Log();
  /// Init the log file
  /// \param filename name for the file
  void Init(const char *filename);
  /// Write Text to logfile
  /// \param debug_text your text
  void Write(std::string debug_text);
  /// Get the date
  std::string logDate(void);
  /// Format to logstyle
  /// \param fmt_str the formatted style
  std::string format(const std::string &fmt_str, ...);

private:
  /// \param filename the name of the logfile
  std::string filename;
};
