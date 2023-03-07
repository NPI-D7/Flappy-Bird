#pragma once
#include <3ds.h>
#include <vector>

namespace Tasks {
void create(ThreadFunc entrypoint);
void destroy(void);
} // namespace Tasks