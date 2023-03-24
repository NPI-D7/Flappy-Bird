#include "Game.hpp"
#include "TEX.h"

int main() {
  rd7_do_splash = true;
  RenderD7::Init::Main("Flappy-Bird");
  RenderD7::Init::NdspFirm();
  RenderD7::FadeIn();
  RenderD7::Scene::Load(std::make_unique<Game>());
  while (RenderD7::MainLoop()) {
    if (d7_hDown & KEY_START) {
      RenderD7::FadeOut();
      RenderD7::ExitApp();
    }
    RenderD7::OnScreen(Top);
    RenderD7::FrameEnd();
  }

  return 0;
}
