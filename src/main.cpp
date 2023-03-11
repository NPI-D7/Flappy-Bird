#include "Game.hpp"
#include "TEX.h"

int main() {
  rd7_do_splash = true;
  RenderD7::Init::Main("Flappy-Bird");
  RenderD7::Init::NdspFirm();
  RenderD7::DoNpiIntro();
  RenderD7::FadeOut();
  RenderD7::Scene::Load(std::make_unique<Game>());
  while (RenderD7::MainLoop()) {
    // RenderD7::Scene::doDraw();
    // RenderD7::Scene::doLogic(d7_hDown, d7_hHeld, d7_hUp, d7_touch);
    if (d7_hDown & KEY_START) {
      RenderD7::FadeIn();
      RenderD7::ExitApp();
    }
    RenderD7::OnScreen(Top);
    RenderD7::FrameEnd();
  }
  RenderD7::Exit::NdspFirm();
  RenderD7::Exit::Main();

  return 0;
}
