#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace RenderD7 {
/// @brief Check if A String ends with
/// @param name Input String
/// @param extensions Extensions to Check for
/// @return Ends with or not
inline bool NameIsEndingWith(const std::string &name,
                             const std::vector<std::string> &extensions) {
  if (name.substr(0, 2) == "._")
    return false;

  if (name.size() == 0)
    return false;

  if (extensions.size() == 0)
    return true;

  for (int i = 0; i < (int)extensions.size(); i++) {
    const std::string ext = extensions.at(i);
    if (strcasecmp(name.c_str() + name.size() - ext.size(), ext.c_str()) == 0)
      return true;
  }

  return false;
}
/// @brief Format Milliseconds to clean string (Stolen from one of my Mc
/// Plugins)
/// @param t_time Time in ms
/// @return String
inline std::string MsTimeFmt(float t_time) {
  std::ostringstream oss;

  if (t_time < 0.001f) {
    oss << std::fixed << std::setprecision(2) << t_time * 1000.0f << "ns";
  } else if (t_time < 1.0f) {
    oss << std::fixed << std::setprecision(2) << t_time << "ms";
  } else if (t_time < 60000.0f) {
    int seconds = static_cast<int>(t_time / 1000.0f);
    float milliseconds = t_time - (seconds * 1000.0f);

    if (seconds > 0) {
      oss << seconds << "s ";
    }
    oss << std::fixed << std::setprecision(2) << milliseconds << "ms";
  } else {
    int minutes = static_cast<int>(t_time / 60000.0f);
    int seconds = static_cast<int>((t_time - (minutes * 60000.0f)) / 1000.0f);
    float milliseconds = t_time - (minutes * 60000.0f) - (seconds * 1000.0f);

    oss << minutes << "m ";
    if (seconds > 0 || milliseconds > 0.0f) {
      oss << seconds << "s ";
    }
    if (milliseconds > 0.0f) {
      oss << std::fixed << std::setprecision(2) << milliseconds << "ms";
    }
  }

  return oss.str();
}
} // namespace RenderD7

template <class T> T GetFileName(T const &path, T const &delims = "/\\") {
  return path.substr(path.find_last_of(delims) + 1);
}
template <class T> T remove_ext(T const &filename) {
  typename T::size_type const p(filename.find_last_of('.'));
  return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

template <typename T> std::string Int_To_Hex(T i) {
  std::stringstream stream;
  stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex
         << i;
  return stream.str();
}