#include "Game.hpp"
#include "TEX.h"
#include "Pipe.hpp"
#include <time.h>
#include "Numbers.hpp"

RenderD7::Sheet stuffs;
RenderD7::Sheet ybirds;
RenderD7::Sprite bgn;
RenderD7::Sprite bgd;
RenderD7::Sprite board;
RenderD7::Sprite plays;
RenderD7::Sprite upipe[5];
RenderD7::Sprite cpipe[5];
RenderD7::Sprite ground[2];
RenderD7::Sprite bscr;
RenderD7::SpriteSheetAnimation ybird;

bool tot = false;
bool menu = true;
bool playing = false;
float birdPOS = 112.5;
float birdv = 0;

float timer = 0;
bool fixedl = false;
float birdr = (birdv/5)*128;

float boardposy;
int sscore = 0;
int best = 0;
Pipe gpipes[5];
Pipe cpipes[5];


Game::Game()
{
    srand(time(NULL));
    stuffs.Load("romfs:/gfx/stuff.t3x");
    ybirds.Load("romfs:/gfx/ybird.t3x");
    bgn.FromSheet(&stuffs, STUFF_BGN);
    bgd.FromSheet(&stuffs, STUFF_BGD);
    plays.FromSheet(&stuffs, STUFF_GETREADY);
    board.FromSheet(&stuffs, STUFF_SCORES);
    Num::Load();
    for (int s = 0; s < 2; s++)
    {
        ground[s].FromSheet(&stuffs, STUFF_GROUND);
    }
    for(int p = 0; p < 5; p++)
    {
        upipe[p].FromSheet(&stuffs, STUFF_PIPEU);
        cpipe[p].FromSheet(&stuffs, STUFF_PIPED);
        cpipe[p].SetCenter(0, 1.0);
        gpipes[p].posx = 86*p + 400;
        gpipes[p].posy = rand() % 80 + 65;
        cpipes[p].posx = gpipes[p].posx;
        cpipes[p].posy = gpipes[p].posy - 52;
    }
    
    ground[0].SetPos(0, 189);
    ground[1].SetPos(400, 189);
    ybird.Setup(&ybirds, 4, 0, 0, 20);
    bscr.FromSheet(&stuffs, STUFF_BOTTOMSCREEN);
    
    plays.SetPos(138, 30);
    boardposy = (240/2) - (board.getHeigh()/2);
}
Game::~Game()
{
    stuffs.Free();
}
void Game::Draw(void) const
{
    RenderD7::OnScreen(Top);
    bgn.Draw();
    
    
    
    if (menu)
    {
        plays.Draw();
    }
    if (!tot)
    {
        for (int i = 0; i < 2; i++)
        {
            ground[i].SetPos(ground[i].getPosX() - 0.5, 189);
            if (ground[i].getPosX() < - 399)
            {
                ground[i].SetPos(400, 189);
            }
            
        }
        
        if (playing)
        {
            for(int p = 0; p < 5; p++)
            {
                upipe[p].SetPos(gpipes[p].posx, gpipes[p].posy);
                upipe[p].Draw();
                cpipe[p].SetPos(cpipes[p].posx, cpipes[p].posy);
                cpipe[p].Draw();
                if (gpipes[p].posx == 77)
                {
                    sscore += 1;
                }
                
                gpipes[p].posx -= 0.5;
                cpipes[p].posx -= 0.5;
                if (gpipes[p].posx < -30)
                {
                    gpipes[p].posy = rand() % 80 + 65;
                    gpipes[p].posx = 400;
                }
                if (cpipes[p].posx < -30)
                {
                    cpipes[p].posy = gpipes[p].posy - 52;
                    cpipes[p].posx = 400;
                }
                
            }
            Num::DrawBig(190, 20, sscore);
        }
    }
    
    if (tot)
    {
        for(int p = 0; p < 5; p++)
        {
            upipe[p].SetPos(gpipes[p].posx, gpipes[p].posy);
            upipe[p].Draw();
            cpipe[p].SetPos(cpipes[p].posx, cpipes[p].posy);
            cpipe[p].Draw();
        }
        board.Draw();
        Num::DrawMin((board.getPosX() + board.getWidth()) - 32, boardposy + 26, sscore);
        Num::DrawMin((board.getPosX() + board.getWidth()) - 32, boardposy + 60, best);
    }

    ybird.Draw();
    for (int s = 0; s < 2; s++)
    {
        ground[s].Draw();
    }
    
    RenderD7::OnScreen(Bottom);
    bscr.Draw();
    RenderD7::DrawTextCentered(0, 210, 1.0f, RenderD7::Color::Hex("#000000"), "Press Start to Exit", 320);
}
void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    birdr = (birdv/5)*2.5;
    if (birdr >= 1.5)
    {
        birdr = 1.5;
    }
    
    if (!tot)
    {
        if (menu)
        {
            birdPOS += birdv;
            birdv += 0.005;
            if (birdv > 0.25)
            {
                birdv = -0.25;
            }
            ybird.Play(1.5);
            ybird.SetPos(77, birdPOS);

            if (hDown & KEY_TOUCH && birdPOS < 120)
            {
                playing = true;
                menu = false;
            }
            
        }
        if (playing)
        {
            birdPOS += birdv;
            birdv += 0.025;
            ybird.Play(4);
            ybird.SetPos(77, birdPOS);
            ybird.SetCenter(DEFAULT_CENTER, DEFAULT_CENTER);
            ybird.SetRotation(birdr);
            if (hDown & KEY_TOUCH)
            {
                birdv = -1;
            }
            if (birdPOS > (189 - ybird.getWidth()/2))
            {
                birdPOS = (189 - ybird.getHeigh()/2);
                playing = false;
                tot = true;
            }
            
        }
        
    }
    if (tot)
    {
        if (sscore > best)
        {
            best = sscore;
        }
        board.SetPos((400/2) - (board.getWidth()/2), boardposy);
        timer +=1;
        if (timer > 60)
        {
            fixedl = true;
        }
        if (fixedl)
        {
            if (hDown & KEY_TOUCH)
            {
                for(int p = 0; p < 5; p++)
                {
                    cpipe[p].SetCenter(0, 1.0);
                    gpipes[p].posx = 86*p + 400;
                    gpipes[p].posy = rand() % 80 + 65;
                    cpipes[p].posx = gpipes[p].posx;
                    cpipes[p].posy = gpipes[p].posy - 52;
                }
                ground[0].SetPos(0, 189);
                ground[1].SetPos(400, 189);
                menu = true;
                tot = false;
                sscore = 0;
                fixedl = false;
            }
        }
    }
}
