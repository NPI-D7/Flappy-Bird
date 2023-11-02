#include "Score.hpp"

#include <filesystem>
#include <fstream>

#define pakfr(x) reinterpret_cast<char*>(&x), sizeof(x)
#define pakfw(x) reinterpret_cast<const char*>(&x), sizeof(x)

struct FBSave {
  uint32_t vrf;
  int score;
};

Score::Score() {
  // Do nothing
}

Score::~Score() {
  // Do nothing
}

void Score::save() {
  std::fstream fbsave(path, std::ios::out | std::ios::binary);
  if (!fbsave.is_open()) {
    return;  // Fail Exit the func
  }
  FBSave s;
  s.vrf = 0x44772673;  // Verification Code
  s.score = val;
  fbsave.write(pakfw(s));
  fbsave.close();
}

void Score::load(const std::string& pth) {
  path = pth;
  // Read in Old Heigscore from <= 1.4.1
  std::fstream fbl142("sdmc:/Flappy-Bird.bin", std::ios::in | std::ios::binary);
  if (fbl142.is_open() && fbl142.good()) {
    fbl142.read(pakfr(val));
    fbl142.close();
    save();  // Save to new File
    remove("sdmc:/Flappy-Bird.bin");
    return;  // Break
  }
  std::fstream fbsave(path, std::ios::in | std::ios::binary);
  if (!fbsave.is_open()) {
    val = 0;
    return;  // Break
  }
  FBSave s;
  fbsave.read(pakfr(s));
  fbsave.close();
  if (s.vrf != 0x44772673) {
    val = 0;
    return;  // Break
  }
  val = s.score;
}

void Score::set(int score) { val = score; }

int Score::get() { return val; }
