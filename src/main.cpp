#include "renderd7.hpp"
#include "TEX.h"
#include "Game.hpp"

int main()
{
    RenderD7::Init::Main("Flappy-Bird");
    RenderD7::Init::NdspFirm(true);
    if (!RenderD7::IsNdspInit())
    {
        RenderD7::Error::DisplayError("Flappy-Bird->RenderD7->Error", "sdmc:/3ds/dspfirm.cdc not found.\nThis means that soundeffects\ncould not be played.\nYou can dump it with the Latest Luma3ds version.\nPress L + DPadDown + Select\nGo to Miscellaneous options...->Dump DSP firmware\nThen Restart this Game.", 10);
    }
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
    RenderD7::Exit::NdspFirm();
    RenderD7::Exit::Main();
    
    return 0;
}
