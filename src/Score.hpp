#pragma once

#include <string>

class Score {
 public:
  Score();
  ~Score();
  void save();
  void load(const std::string& pth);
  void set(int score);
  int get();

 private:
  int val = 0;
  std::string path;
};