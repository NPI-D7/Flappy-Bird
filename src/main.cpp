#include "renderd7.hpp"

int main()
{
    RenderD7::Init::Main("Flappy-Bird");
    while (RenderD7::MainLoop())
    {
        if (d7_hDown && KEY_START)
        {
            RenderD7::ExitApp();
        }
        
    }
    RenderD7::Exit::Main();
    
    return 0;
}