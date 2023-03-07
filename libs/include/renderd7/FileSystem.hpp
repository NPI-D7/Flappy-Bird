// FileSystem based on libphyfs based on
// https://github.com/TurtleP/3ds-examples/blob/fs/physfs/fs/physfs/include/filesystem.h
#pragma once
#include <string>
#include <vector>

namespace RenderD7 {
namespace FileSystem {
struct Entry {
  std::string path;
  std::string name;
  bool dir = false;
};

std::vector<RenderD7::FileSystem::Entry> GetDirContent(std::string path);
} // namespace FileSystem
} // namespace RenderD7