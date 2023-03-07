#include <renderd7/Clock.hpp>

namespace rnd7 {
enum class TweenType : int { Position = 1, Color, Alpha };

enum class TweenLoop : int {
  None = 1,
  Loop = 2,
};

enum class TweenDirection : int { Current, Forward, Backward };

enum class TweenState : int { Playing = 1, Stopped };
class Tween {
public:
  Tween(float from, float to, float duration, TweenLoop loop, TweenState state);
};
} // namespace rnd7
