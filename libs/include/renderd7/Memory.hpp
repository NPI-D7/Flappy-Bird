#pragma once

#include <cstdint>
#include <memory>

namespace RenderD7 {
namespace Memory {
/// @brief Metriks struct For the Internal Tracker
struct memory_metrics {
  uint32_t t_TotalAllocated = 0; ///< Total Allocated Memory
  uint32_t t_TotalFreed = 0;     ///< Total Deleted Memory
  /// @brief Gets the Currently Allocated Memory
  uint32_t t_CurrentlyAllocated() { return t_TotalAllocated - t_TotalFreed; }
};
/// @brief Get Total Allocated Memory
/// @return Total Allocated Memory
size_t GetTotalAllocated();
/// @brief Get Total Deleted Memory
/// @return Total Deleted Memory
size_t GetTotalFreed();
/// @brief Get Current Allocated Memory
/// @return Current Allocated Memory
size_t GetCurrent();
} // namespace Memory
} // namespace RenderD7
