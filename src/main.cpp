#include "renderd7.hpp"
#include "TEX.h"
#include "Game.hpp"

int main()
{
    RenderD7::Init::Main("Flappy-Bird");
    RenderD7::Scene::Load(std::make_unique<Game>());
    while (RenderD7::MainLoop())
    {
        RenderD7::Scene::doDraw();
        RenderD7::Scene::doLogic(d7_hDown, d7_hHeld, d7_hUp, d7_touch);
        if (d7_hDown & KEY_START)
        {
            RenderD7::ExitApp();
        }
        RenderD7::FrameEnd();
    }
    RenderD7::Exit::Main();
    
    return 0;
}
