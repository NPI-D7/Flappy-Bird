#include "renderd7.hpp"
#include "TEX.h"

RenderD7::Sheet stuff;

int main()
{
    RenderD7::Init::Main("Flappy-Bird");
    stuff.Load("romfs:/gfx/stuff.t3x");
    RenderD7::Sprite spr;
    spr.FromSheet(&stuff, STUFF_BGN);
    while (RenderD7::MainLoop())
    {
        RenderD7::OnScreen(Top);
        spr.Draw();
        if (d7_hDown && KEY_START)
        {
            RenderD7::ExitApp();
        }
        C3D_FrameEnd(0);
    }
    RenderD7::Exit::Main();
    
    return 0;
}