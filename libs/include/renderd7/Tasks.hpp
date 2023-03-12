#pragma once
#include <3ds.h>
#include <vector>

namespace RenderD7 {
namespace Tasks {
/// @brief Push A Task
/// @param entrypoint Function of Your Task
void create(ThreadFunc entrypoint);
/// @brief Destroy all Tasks
void destroy(void);
} // namespace Tasks
} // namespace RenderD7