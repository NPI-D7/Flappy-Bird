#pragma once
// Base includes
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
// 3ds does not support std::chrono
#include <3ds.h>

/// @brief 3ds System Ticks per milli second
#define TICKS_PER_MSEC 268111.856

#define f2s(x_) #x_
#define scomb(x1, x2) std::string(x1 + x2)

namespace RenderD7 {
namespace Ftrace {
/// @brief Result of FTrace
struct FTRes {
  std::string group;     ///< Group of the Trace
  std::string func_name; ///< Function Name

  uint64_t time_start; ///< when started
  uint64_t time_end;   ///< when stopped
  float time_of;       ///< stop - start (how long)
};

/// @brief Map of Traces
extern std::map<std::string, RenderD7::Ftrace::FTRes> rd7_traces;

/// @brief Set a Start TracePoint
/// @param group Set a Group Name
/// @param func_name Set a Function Name
inline void Beg(std::string group, std::string func_name) {
  std::string trace_id = scomb(group, func_name);
  rd7_traces[trace_id].group = group;
  rd7_traces[trace_id].func_name = func_name;
  rd7_traces[trace_id].time_start = svcGetSystemTick();
}
/// @brief Set an End TracePoint
/// @param group Set a Group Name
/// @param func_name Set a Function Name
inline void End(std::string group, std::string func_name) {
  std::string trace_id = scomb(group, func_name);
  rd7_traces[trace_id].time_end = svcGetSystemTick();
  rd7_traces[trace_id].time_of = static_cast<float>(
      rd7_traces[trace_id].time_end / (float)TICKS_PER_MSEC -
      rd7_traces[trace_id].time_start / (float)TICKS_PER_MSEC);
}
} // namespace Ftrace
} // namespace RenderD7