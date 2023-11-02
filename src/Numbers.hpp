#pragma once
#include "rd7.hpp"

// Defines
#define NUM_BIG_0 0
#define NUM_BIG_1 1
#define NUM_BIG_2 2
#define NUM_BIG_3 3
#define NUM_BIG_4 4
#define NUM_BIG_5 5
#define NUM_BIG_6 6
#define NUM_BIG_7 7
#define NUM_BIG_8 8
#define NUM_BIG_9 9
#define NUM_MIN_0 10
#define NUM_MIN_1 11
#define NUM_MIN_2 12
#define NUM_MIN_3 13
#define NUM_MIN_4 14
#define NUM_MIN_5 15
#define NUM_MIN_6 16
#define NUM_MIN_7 17
#define NUM_MIN_8 18
#define NUM_MIN_9 19

namespace Num {
void Load();
void DrawBig(int x, int y, int num);
void DrawMin(int x, int y, int num);
}  // namespace Num