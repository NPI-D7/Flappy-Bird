#include "Game.hpp"
#include "TEX.h"

RenderD7::Sheet stuffs;
RenderD7::Sheet ybirds;
RenderD7::Sprite bgn;
RenderD7::Sprite bgd;
RenderD7::Sprite ground[2];
RenderD7::Sprite bscr;
RenderD7::SpriteSheetAnimation ybird;

Game::Game()
{
    stuffs.Load("romfs:/gfx/stuff.t3x");
    ybirds.Load("romfs:/gfx/ybird.t3x");
    bgn.FromSheet(&stuffs, STUFF_BGN);
    bgd.FromSheet(&stuffs, STUFF_BGD);
    for (int s = 0; s < 2; s++)
    {
        ground[s].FromSheet(&stuffs, STUFF_GROUND);
    }
    ground[0].SetPos(0, 189);
    ground[1].SetPos(399, 189);
    ybird.Setup(&ybirds, 4, 0, 0, 20);
    bscr.FromSheet(&stuffs, STUFF_BOTTOMSCREEN);
}
Game::~Game()
{
    stuffs.Free();
}
void Game::Draw(void) const
{
    RenderD7::OnScreen(Top);
    bgn.Draw();
    for (int s = 0; s < 2; s++)
    {
        ground[s].Draw();
    }
    
    ybird.Draw();

    RenderD7::OnScreen(Bottom);
    bscr.Draw();
    RenderD7::DrawTextCentered(0, 210, 1.0f, RenderD7::Color::Hex("#000000"), "Press Start to Exit", 320);
}
void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    ybird.Play(2);
    ground[0].SetPos(ground[0].getPosX() -0.5, 189);
    if (ground[0].getPosX() < -399)
    {
        ground[0].SetPos(0, 189);
    }
    ground[1].SetPos(ground[1].getPosX() -0.5, 189);
    if (ground[1].getPosX() < 1)
    {
        ground[1].SetPos(399, 189);
    }
    
}
