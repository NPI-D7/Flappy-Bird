#include "Game.hpp"
#include "TEX.h"
#include "Pipe.hpp"
#include <time.h>
#include "Numbers.hpp"
#include "sound.hpp"

RenderD7::Sheet stuffs;
RenderD7::Sheet ybirds;
RenderD7::Sprite bgn;
RenderD7::Sprite bgd;
RenderD7::Sprite board;
RenderD7::Sprite plays;
RenderD7::Sprite medalbronze;
RenderD7::Sprite medalsilver;
RenderD7::Sprite medalgold;
RenderD7::Sprite medalplatin;
RenderD7::Sprite newss;
RenderD7::Sprite gameovre;
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
bool hitd = false;

float timer = 0;
bool fixedl = false;
float birdr = (birdv/5)*128;

float boardposy;
int sscore = 0;

bool newbest= false;
Pipe gpipes[5];
Pipe cpipes[5];

sound* fly = NULL;
sound* point = NULL;
sound* die = NULL;
sound* hit = NULL;
sound* swoosh = NULL;

int bgrr = 0;

int LoadHighScore() {
    FILE *scorefile = fopen("sdmc:/Flappy-Bird.bin", "rb");
    
    if(!scorefile)
        return 0;
    
    int ret;
    fread(&ret, sizeof(int), 1, scorefile);
    fclose(scorefile);
    
    return ret;
}
int best = LoadHighScore();
void SaveHighScore(int val) {
    FILE *scorefile = fopen("sdmc:/Flappy-Bird.bin", "wb");
    
    fwrite(&val, sizeof(int), 1, scorefile);
    fclose(scorefile);
}

int birdt = 0;
Game::Game()
{
    srand(time(NULL));
    stuffs.Load("romfs:/gfx/stuff.t3x");
    birdt = rand() % 3 + 0;
    switch (birdt)
    {
    case 0:
        ybirds.Load("romfs:/gfx/ybird.t3x");
        break;
    case 1:
        ybirds.Load("romfs:/gfx/bbird.t3x");
        break;
    case 2:
        ybirds.Load("romfs:/gfx/rbird.t3x");
        break;
    default:
        ybirds.Load("romfs:/gfx/ybird.t3x");
        break;
    }
    
    bgn.FromSheet(&stuffs, STUFF_BGN);
    bgd.FromSheet(&stuffs, STUFF_BGD);
    plays.FromSheet(&stuffs, STUFF_GETREADY);
    board.FromSheet(&stuffs, STUFF_SCORES);
    medalbronze.FromSheet(&stuffs, STUFF_MEDALBRONZE);
    medalsilver.FromSheet(&stuffs, STUFF_MEDALSILVER);
    medalgold.FromSheet(&stuffs, STUFF_MEDALGOLD);
    medalplatin.FromSheet(&stuffs, STUFF_MEDALPLATIN);
    gameovre.FromSheet(&stuffs, STUFF_GAMEOVER);
    newss.FromSheet(&stuffs, STUFF_NEW);
    gameovre.SetPos((400/2) - (gameovre.getWidth()/2), 10);
    if (RenderD7::IsNdspInit())
    {
        fly = new sound("romfs:/sfx/wing.wav", 1);
        point = new sound("romfs:/sfx/point.wav", 2);
        die = new sound("romfs:/sfx/die.wav", 3);
        hit = new sound("romfs:/sfx/hit.wav", 4);
        swoosh = new sound("romfs:/sfx/swoosh.wav", 5);
    }
    {
        /* code */
    }
    bgrr = rand() % 2 + 0;
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
    boardposy = 260;
    
}
Game::~Game()
{
    stuffs.Free();
    ybirds.Free();
}
void Game::Draw(void) const
{
    RenderD7::OnScreen(Top);
    if (bgrr == 0) bgn.Draw();
    if (bgrr != 0) bgd.Draw();
    
    
    
    if (menu)
    {
        plays.Draw();
        RenderD7::DrawTextCentered(0, 240 - RenderD7::GetTextHeight(0.4f, "(c) .GEARS 2013, NPI-D7 2022"), 0.4f, RenderD7::Color::Hex("#eeeeee"), "(c) .GEARS 2013, NPI-D7 2022", 400);
    }
    if (!tot)
    {
        for (int i = 0; i < 2; i++)
        {
            ground[i].SetPos(ground[i].getPosX() - 0.5, 189);
            if (ground[i].getPosX() == -400)
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
                if ((gpipes[p].posx + (upipe[0].getWidth()/2)) == 77)
                {
                    point->play();
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
    }

    ybird.Draw();
    for (int s = 0; s < 2; s++)
    {
        ground[s].Draw();
    }
    if (tot)
    {
        board.Draw();
        Num::DrawMin((board.getPosX() + board.getWidth()) - 32, boardposy + 26, sscore);
        Num::DrawMin((board.getPosX() + board.getWidth()) - 32, boardposy + 60, best);
        newss.SetPos(board.getPosX() + 66, boardposy + 62);
        if (newbest)
        {
            newss.Draw();
        }
        
        switch(sscore)
        {
            case 10 ... 19:
            medalbronze.SetPos(board.getPosX() + 20, boardposy + 32);
            medalbronze.Draw();
            break;
            case 20 ... 29:
            medalsilver.SetPos(board.getPosX() + 20, boardposy + 32);
            medalsilver.Draw();
            break;
            case 30 ... 39:
            medalgold.SetPos(board.getPosX() + 20, boardposy + 32);
            medalgold.Draw();
            break;
            case 40 ... 999:
            medalplatin.SetPos(board.getPosX() + 20, boardposy + 32);
            medalplatin.Draw();
            break;
            default:
            break;
        }
        gameovre.Draw();
    }
    
    RenderD7::OnScreen(Bottom);
    bscr.Draw();
    RenderD7::DrawTextCentered(0, 210, 0.8f, RenderD7::Color::Hex("#000000"), "Press Start to Exit", 320);
}
void Game::Logic(u32 hDown, u32 hHeld, u32 hUp, touchPosition touch)
{
    if (sscore >= 999)
    {
        sscore = 999;
    }
    birdr = (birdv/5)*2.5;
    if (birdr >= 1.5)
    {
        birdr = 1.5;
    }
    
    
    if (menu)
    {
        playing = false;
        
        birdPOS += birdv;
        birdv += 0.005;
        if (birdv > 0.25)
        {
            birdv = -0.25;
        }
        ybird.Play(1.5);
        ybird.SetPos(77, birdPOS);
        timer++;
        if (timer > 10 && hDown & KEY_TOUCH)
        {
            playing = true;

            menu = false;
            fixedl = false;
            timer = 0;
        }
    }
    if (playing)
    {
        birdPOS += birdv;
        birdv += 0.026;
        ybird.Play(4);
        ybird.SetPos(77, birdPOS);
        ybird.SetCenter(DEFAULT_CENTER, DEFAULT_CENTER);
        ybird.SetRotation(birdr);
        if (hDown & KEY_TOUCH && !hitd)
        {
            fly->play();
            birdv = -1.1;
        }
        //Colissiob
        for (int i = 0; i < 5; i++)
        {
            if (((birdPOS - ybird.getHeigh()/2) < cpipes[i].posy) && (77 + ybird.getWidth()/2) > cpipes[i].posx && (77 - ybird.getWidth()/2) < (cpipes[i].posx + cpipe[i].getWidth()) || ((birdPOS + ybird.getHeigh()/2) > gpipes[i].posy) && (77 + ybird.getWidth()/2) > gpipes[i].posx && (77 - ybird.getWidth()/2) < (gpipes[i].posx + upipe[i].getWidth()))
            {
                hit->play();
                die->play();
                boardposy  = 4000; //As far away as possible
                hitd = true;
                tot = true;
            }
        }
    
        if (birdPOS > (189 - ybird.getWidth()/2))
        {
            if (!hitd) hit->play();
            if (!hitd) die->play();
            birdPOS = (189 - ybird.getHeigh()/2);
            playing = false;
            boardposy  = 240;
            tot = true;
        }
            
    }
    if (tot)
    {
        
        if (sscore > best)
        {
            newbest = true;
            best = sscore;
            SaveHighScore(best);
        }
        board.SetPos((400/2) - (board.getWidth()/2), boardposy);
        timer +=1;
        birdPOS += birdv;
        birdv += 0.026;
        if (birdPOS > (189 - ybird.getWidth()/2))
        {
            birdPOS = (189 - ybird.getHeigh()/2);
        }
        if (timer > 60)
        {
            fixedl = true;
        }
        //if (fixedl)
        //{
            boardposy-=4;
            if (boardposy < (240/2) - (board.getHeigh()/2))
            {
                boardposy = (240/2) - (board.getHeigh()/2);
            }
            if (hDown & KEY_TOUCH && boardposy == (240/2) - (board.getHeigh()/2))
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
                
                sscore = 0;
                fixedl = false;
                birdPOS = 112.5;
                timer = 0;
                swoosh->play();
                menu = true;
                newbest = false;
                bgrr = rand() % 2 + 0;
                hitd = false;
                tot = false;
                
            }
       // }
    }
}
