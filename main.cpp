#define _USE_MATH_DEFINES
#include <iostream>
#include "common.h"
#include <cstdlib>
#include <cmath>
#include "base_object.h"
#include "Player_Object.h"
#include "Ball_Object.h"
#include "img_link.h"
#include "game_status_machine.h"


// BaseObject g_BackGround;
PlayerObject g_Character_1;
PlayerObject g_Character_2;
BallObject g_Ball;

bool InitData()
{
  bool success = true;
  int ret = SDL_Init(SDL_INIT_VIDEO);
  if(ret < 0)
  {
    return false;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

  g_Window = SDL_CreateWindow("GAME SDL2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);

  if(g_Window == NULL)
  {
    success = false;
  }
  else{
    g_Screen = SDL_CreateRenderer(g_Window,-1,SDL_RENDERER_ACCELERATED);
    if(g_Screen == NULL)
    {
        success = false;
    }
    else{
        SDL_SetRenderDrawColor(g_Screen,255,255,255,255);
        int imgFlag = IMG_INIT_PNG;
        if(!(IMG_Init(imgFlag) && imgFlag))
        {
            success = false;
        }
    }
  }
    return success;
}

void Close()
{
    g_BackGround.Free();
    SDL_DestroyRenderer(g_Screen);
    g_Screen = NULL;

    SDL_DestroyWindow(g_Window);
    g_Window = NULL;

    IMG_Quit();
    SDL_Quit();
}
 
// bool LoadBackGround()
// {
//     bool ret = g_BackGround.LoadImage(MENU_BACKGROUND,g_Screen);

//     if(ret == false)
//     {
//         return false;
//     }
//     return true;
// }

void angle()
{
    float x = std::abs(g_Ball.x_center -g_Character_1.x_center);
    std::cout<<g_Ball.x_center<<" "<< g_Ball.y_center<<" "<<g_Character_1.x_center<<" "<< g_Character_1.y_center<<std::endl;
    float v = sqrt(pow(std::abs(g_Ball.x_center -g_Character_1.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_1.y_center),2));

    g_Ball.angle = std::acos(x / v);

    g_Ball.angle = g_Ball.angle * 180.0 / M_PI;
    std::cout<<g_Ball.angle<<std::endl;
}

void Force()
{
    if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_1.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_1.y_center),2)) < (25+7) && g_Ball.Force == 0)
    {
        if(g_Ball.x_center > g_Character_1.x_center )
        {
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 3;
                std::cout<<"3"<<std::endl;
            }
            else{
                g_Ball.corner = 2;
                std::cout<<"2"<<std::endl;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 4;
                std::cout<<"4"<<std::endl;
            }
            else{
                g_Ball.corner = 1;
                std::cout<<"1"<<std::endl;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100;
        angle();
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_1.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_1.y_center),2)) < (25+7) && g_Ball.Force != 0)
    {
        if(g_Ball.x_center > g_Character_1.x_center )
        {
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 3;
                std::cout<<"3"<<std::endl;
            }
            else{
                g_Ball.corner = 2;
                std::cout<<"2"<<std::endl;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 4;
                std::cout<<"4"<<std::endl;
            }
            else{
                g_Ball.corner = 1;
                std::cout<<"1"<<std::endl;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100 - g_Ball.Force;
        angle();
    }
    else if(g_Ball.x_pos_ <= 0  && g_Ball.Force != 0)
    {
        if(g_Ball.corner == 1)
        {
            g_Ball.corner = 2;
        }
        if(g_Ball.corner == 4)
        {
            g_Ball.corner = 3;
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = g_Ball.Force;
        g_Ball.angle = g_Ball.angle;
    }
    else if(g_Ball.x_pos_ + g_Ball.width_frame >=SCREEN_WIDTH   && g_Ball.Force != 0)
    {
        if(g_Ball.corner == 3)
        {
            g_Ball.corner = 4;
        }
        if(g_Ball.corner == 2)
        {
            g_Ball.corner = 1;
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = g_Ball.Force;
        g_Ball.angle = g_Ball.angle;
    }
    else if(g_Ball.x_pos_ + g_Ball.width_frame >=SCREEN_WIDTH   && g_Ball.Force != 0)
    {
        if(g_Ball.corner == 3)
        {
            g_Ball.corner = 4;
        }
        if(g_Ball.corner == 2)
        {
            g_Ball.corner = 1;
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = g_Ball.Force;
        g_Ball.angle = g_Ball.angle;
    }
    else if(g_Ball.x_pos_ + g_Ball.width_frame >=SCREEN_WIDTH   && g_Ball.Force != 0)
    {
        if(g_Ball.corner == 3)
        {
            g_Ball.corner = 4;
        }
        if(g_Ball.corner == 2)
        {
            g_Ball.corner = 1;
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = g_Ball.Force;
        g_Ball.angle = g_Ball.angle;
    }
    else if(g_Ball.y_pos_ <= 0   && g_Ball.Force != 0)
    {
        if(g_Ball.corner == 2)
        {
            g_Ball.corner = 3;
        }
        if(g_Ball.corner == 1)
        {
            g_Ball.corner = 4;
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = g_Ball.Force;
        g_Ball.angle = g_Ball.angle;
    }
    else if(g_Ball.y_pos_ + g_Ball.height_frame >=SCREEN_HEIGHT   && g_Ball.Force != 0)
    {
        if(g_Ball.corner == 3)
        {
            g_Ball.corner = 2;
        }
        if(g_Ball.corner == 4)
        {
            g_Ball.corner = 1;
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = g_Ball.Force;
        g_Ball.angle = g_Ball.angle;
    }

}

void BallMove()
{
    if(g_Ball.corner == 1)
    {
        if(g_Ball.Force > 0)
        {
            std::cout<<"tinh cos: "<<g_Ball.angle<<" "<<std::cos(g_Ball.angle* M_PI / 180.0)<<std::endl;
            g_Ball.x_pos_ -= (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            g_Ball.y_pos_ -= (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
            // std::cout<<"hehe"<<std::endl;
        }
        else{
            std::cout<<"1-here"<<std::endl;
            g_Ball.is_move_ = false;
            // std::cout<<"hehe"<<std::endl;
            g_Ball.Force = 0;
            g_Ball.angle = 0;
            g_Ball.corner = 0;
        }
    }
    else if(g_Ball.corner == 2)
    {
        if(g_Ball.Force > 0)
        {
            // std::cout<<g_Ball.x_pos_ << " " << g_Ball.y_pos_<<std::endl;
            std::cout<<"tinh cos: "<<g_Ball.angle<<" "<<std::cos(g_Ball.angle* M_PI / 180.0)<<std::endl;
            g_Ball.x_pos_ += (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            g_Ball.y_pos_ -= (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
            // std::cout<<g_Ball.x_pos_ << " " << g_Ball.y_pos_<<std::endl;
        }
        else{
            std::cout<<"2-here"<<std::endl;
            g_Ball.is_move_ = false;
            g_Ball.Force = 0;
            g_Ball.angle = 0;
            g_Ball.corner = 0;
        }
    }
    else if(g_Ball.corner == 3)
    {
        if(g_Ball.Force > 0)
        {
            std::cout<<"tinh cos: "<<g_Ball.angle<<" "<<std::cos(g_Ball.angle* M_PI / 180.0)<<std::endl;
            g_Ball.x_pos_ += (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            g_Ball.y_pos_ += (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
        }
        else{
            std::cout<<"3-here"<<std::endl;
            g_Ball.is_move_ = false;
            g_Ball.Force = 0;
            g_Ball.angle = 0;
            g_Ball.corner = 0;
        }
    }
    else if(g_Ball.corner == 4)
    {
        if(g_Ball.Force > 0)
        {
            std::cout<<"tinh cos: "<<g_Ball.angle<<" "<<std::cos(g_Ball.angle* M_PI / 180.0)<<std::endl;
            g_Ball.x_pos_ -= (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            g_Ball.y_pos_ += (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
        }
        else{
            std::cout<<"4-here"<<std::endl;
            g_Ball.is_move_ = false;
            g_Ball.Force = 0;
            g_Ball.angle = 0;
            g_Ball.corner = 0;
        }
    }
    else{}

}

int main( int argc, char *argv[] )
{
    if(InitData() == false)
    {
        return -1;
    }

    if(g_Menu.LoadMenu() == false)
    {
        return -1;
    }

    std::cout<<(g_Character_1.LoadImg(PLAYER_BLUE_TEAM_SPRITE, g_Screen)?"success":"Failed to load player image")<<std::endl;
    g_Character_1.Set_Clip();

    std::cout<<(g_Ball.LoadImg(BALL, g_Screen)?"success to load ball image":"Failed to load ball image")<<std::endl;
    g_Ball.x_pos_ = 100;
    g_Ball.y_pos_ = 200;

    std::cout<<g_Character_1.GetRect().w<<" "<<g_Character_1.GetRect().h<<std::endl;
    

    while(!isQuit)
    {
        if(SDL_PollEvent(&g_Event))
        {

            if(g_Event.type == SDL_QUIT)
            {
                isQuit = true;
            }
            g_Character_1.HandleInputAction(g_Event,g_Screen);
        }
        SDL_RenderClear(g_Screen);
        // SDL_SetRenderDrawColor(g_Screen,255,255,255,255);
        game_status_machine();
        g_BackGround.Render(g_Screen,NULL);
        g_Menu.ShowMenu();
        g_Character_1.Show(g_Screen);
        g_Ball.Show(g_Screen);
        g_Character_1.Center();
        g_Ball.Center();
        Force();
        if(g_Ball.is_move_ == true) BallMove();

        SDL_RenderPresent(g_Screen);
        SDL_Delay(16);
    }

    Close();
    return 0;
   
}