#define _USE_MATH_DEFINES
#include <iostream>
#include "common.h"
#include <cstdlib>
#include <cmath>
#include "base_object.h"
#include "Player_Object.h"
#include "Ball_Object.h"
#include "ImpTimer.h"

BaseObject g_BackGround;
PlayerObject g_Character_1;
PlayerObject g_Character_2;
PlayerObject g_Character_3;
PlayerObject g_Character_4;
BallObject g_Ball;

int is_chances = 0;
int is_chances_1 = 0;

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
 
bool LoadBackGround()
{
    bool ret = g_BackGround.LoadImage("main1.png",g_Screen);

    if(ret == false)
    {
        return false;
    }
    return true;
}

void renderText(SDL_Renderer *m_renderer, int xp, int yp, int w, int h, std::string addressOfFont, int fontsize, int R, int G, int B, int A, std::string S)
{
    TTF_Font *Sans = TTF_OpenFont(addressOfFont.c_str(), fontsize);
    SDL_Color textcolor = {(Uint8)R, (Uint8)G, (Uint8)B, (Uint8)A};
    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, S.c_str(), textcolor);
    SDL_Texture *message = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_Rect messageRect;
    messageRect.x = xp;
    messageRect.y = yp;
    messageRect.w = w;
    messageRect.h = h;
    SDL_RenderCopy(m_renderer, message, NULL, &messageRect);
    SDL_DestroyTexture(message);
    TTF_CloseFont(Sans);
}

// Lỗi dính các trường hợp người kẹt ngoài biên
void AutoMove(PlayerObject *g_Character_)
{
    // std::cout<<g_Character_->x_pos_<<std::endl;
    // std::cout<<g_Character_->y_pos_<<std::endl;
    // trả input về 0 mỗi lần di chuyển xong
    if(g_Character_->x_pos_ >= -10 && g_Character_->x_pos_ + g_Character_->width_frame <= SCREEN_WIDTH + 10 && g_Character_->y_pos_ >= -10 && g_Character_->y_pos_ + g_Character_->height_frame <= SCREEN_HEIGHT + 10){
        if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 250)
        {
            if(g_Ball.x_center > g_Character_->x_center)
            {
                // g_Character_->x_pos_ += 5;
                std::cout<<"1"<<std::endl;
                g_Character_->status = 0;
                g_Character_->input_type.right = 1;
            }
            if(g_Ball.y_center > g_Character_->y_center)
            {
                // g_Character_->y_pos_ +=5;
                std::cout<<"2"<<std::endl;
                g_Character_->status = 3;
                g_Character_->input_type.down = 1;
            }
            if(g_Ball.x_center < g_Character_->x_center)
            {
                // g_Character_->x_pos_ -=5;
                std::cout<<"3"<<std::endl;
                g_Character_->status = 1;
                g_Character_->input_type.left = 1;
            }
            if(g_Ball.y_center < g_Character_->y_center)
            {
                // g_Character_->y_pos_ -=5;
                std::cout<<"4"<<std::endl;
                g_Character_->status = 2;
                g_Character_->input_type.up = 1;
            }
        }
        else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) < 200)
        {
            if(g_Ball.x_center > g_Character_->x_center)
            {
                // g_Character_->x_pos_ -= 5;
                std::cout<<"5"<<std::endl;
                g_Character_->status = 1;
                g_Character_->input_type.left = 1;
            }
            if(g_Ball.y_center > g_Character_->y_center)
            {
                // g_Character_->y_pos_ -=5;
                std::cout<<"6"<<std::endl;
                g_Character_->status = 2;
                g_Character_->input_type.up = 1;
            }
            if(g_Ball.x_center < g_Character_->x_center)
            {
                // g_Character_->x_pos_ +=5;
                std::cout<<"7"<<std::endl;
                g_Character_->status = 0;
                g_Character_->input_type.right = 1;
            }
            if(g_Ball.y_center < g_Character_->y_center)
            {
                // g_Character_->y_pos_ +=5;
                std::cout<<"8"<<std::endl;
                g_Character_->status = 3;
                g_Character_->input_type.down = 1;
            }
        }
        // else if (sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 300)
        // {
        //     if(g_Character_->x_pos_ > 300)
        //     {
        //         g_Character_->status = 0;
        //         g_Character_->input_type.right = 1;
        //     }
        // }
        else{
            std::cout<<"9"<<std::endl;
            g_Character_->status = 0;
            g_Character_->input_type.left = 0;
            g_Character_->input_type.right = 0;
            g_Character_->input_type.up = 0;
            g_Character_->input_type.down = 0;
        }
    }

}

void angle(PlayerObject *g_Character_)
{
    float x = std::abs(g_Ball.x_center -g_Character_->x_center);
    // std::cout<<g_Ball.x_center<<" "<< g_Ball.y_center<<" "<<g_Character_1.x_center<<" "<< g_Character_1.y_center<<std::endl;
    float v = sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2));

    g_Ball.angle = std::acos(x / v);

    g_Ball.angle = g_Ball.angle * 180.0 / M_PI;
    // std::cout<<g_Ball.angle<<std::endl;
}

void Force()
{
    if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_1.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_1.y_center),2)) < 60 && g_Ball.Force == 0)
    {
        if(g_Ball.x_center > g_Character_1.x_center )
        {
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100;
        angle(&g_Character_1);
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_1.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_1.y_center),2)) < 60 && g_Ball.Force != 0)
    {
        if(g_Ball.x_center > g_Character_1.x_center )
        {
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_1.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100 - g_Ball.Force;
        angle(&g_Character_1);
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_2.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_2.y_center),2)) < 60 && g_Ball.Force == 0)
    {
        if(g_Ball.x_center > g_Character_2.x_center )
        {
            if(g_Ball.y_center > g_Character_2.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_2.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100;
        angle(&g_Character_2);
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_2.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_2.y_center),2)) < 60 && g_Ball.Force != 0)
    {
        if(g_Ball.x_center > g_Character_2.x_center )
        {
            if(g_Ball.y_center > g_Character_2.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_2.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100 - g_Ball.Force;
        angle(&g_Character_2);
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_3.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_3.y_center),2)) < 60 && g_Ball.Force == 0)
    {
        if(g_Ball.x_center > g_Character_3.x_center )
        {
            if(g_Ball.y_center > g_Character_3.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_3.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100;
        angle(&g_Character_3);
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_3.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_3.y_center),2)) < 60 && g_Ball.Force != 0)
    {
        if(g_Ball.x_center > g_Character_3.x_center )
        {
            if(g_Ball.y_center > g_Character_3.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_3.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100 - g_Ball.Force;
        angle(&g_Character_4);
    }
     else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_4.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_4.y_center),2)) < 60 && g_Ball.Force == 0)
    {
        if(g_Ball.x_center > g_Character_4.x_center )
        {
            if(g_Ball.y_center > g_Character_4.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_4.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100;
        angle(&g_Character_4);
    }
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_4.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_4.y_center),2)) < 60 && g_Ball.Force != 0)
    {
        if(g_Ball.x_center > g_Character_4.x_center )
        {
            if(g_Ball.y_center > g_Character_4.y_center)
            {
                g_Ball.corner = 3;
            }
            else{
                g_Ball.corner = 2;
            }
        }
        else{
            if(g_Ball.y_center > g_Character_4.y_center)
            {
                g_Ball.corner = 4;
            }
            else{
                g_Ball.corner = 1;
            }
        }
        g_Ball.is_move_ = true;
        g_Ball.Force = 100 - g_Ball.Force;
        angle(&g_Character_4);
    }

    if(g_Ball.x_pos_ >= -10 && g_Ball.x_pos_<= 10  && g_Ball.Force != 0)
    {
        std::cout<<"hehe"<<std::endl;
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
        std::cout<<g_Ball.Force<<std::endl;
        std::cout<<g_Ball.angle<<std::endl;
    }
    else if(g_Ball.x_pos_ + g_Ball.width_frame <=SCREEN_WIDTH + 10 && g_Ball.x_pos_ + g_Ball.width_frame >=SCREEN_WIDTH - 10  && g_Ball.Force != 0)
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
    else if(g_Ball.y_pos_ >= -10 && g_Ball.y_pos_ <= 10  && g_Ball.Force != 0)
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
    else if(g_Ball.y_pos_ + g_Ball.height_frame <=SCREEN_HEIGHT + 10 && g_Ball.y_pos_ + g_Ball.height_frame >=SCREEN_HEIGHT - 10   && g_Ball.Force != 0)
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
    else{
        if(g_Ball.x_pos_ < -10) g_Ball.x_pos_ +=5;
        if(g_Ball.y_pos_ < -10) g_Ball.y_pos_ +=5;
        if(g_Ball.x_pos_ + g_Ball.width_frame > SCREEN_WIDTH + 10) g_Ball.x_pos_ -=5;
        if(g_Ball.y_pos_ + g_Ball.height_frame > SCREEN_HEIGHT + 10) g_Ball.y_pos_ -=5;
    }

}

void BallMove()
{
    if(g_Ball.corner == 1)
    {
        if(g_Ball.Force > 0)
        {
            if(g_Ball.x_pos_ >=0) g_Ball.x_pos_ -= (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ >=0) g_Ball.y_pos_ -= (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
            // std::cout<<"hehe"<<std::endl;
        }
        else{
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
            if(g_Ball.x_pos_ + g_Ball.width_frame <= SCREEN_WIDTH) g_Ball.x_pos_ += (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ >=0) g_Ball.y_pos_ -= (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
            // std::cout<<g_Ball.x_pos_ << " " << g_Ball.y_pos_<<std::endl;
        }
        else{
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
            if(g_Ball.x_pos_ + g_Ball.width_frame <= SCREEN_WIDTH) g_Ball.x_pos_ += (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ + g_Ball.height_frame <= SCREEN_HEIGHT) g_Ball.y_pos_ += (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
        }
        else{
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
            if(g_Ball.x_pos_ >= 0) g_Ball.x_pos_ -= (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ + g_Ball.height_frame <= SCREEN_HEIGHT) g_Ball.y_pos_ += (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
            g_Ball.Force -= (100 /5);
        }
        else{
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
    ImpTimer fps;
    if(InitData() == false)
    {
        return -1;
    }

    if(LoadBackGround() == false)
    {
        return -1;
    }

    g_Character_1.LoadImg("player_right.png", g_Screen);
    g_Character_1.Set_Clip();
    g_Character_1.x_pos_ = 200;
    g_Character_1.y_pos_ = 600;

    g_Character_2.LoadImg("player_right.png", g_Screen);
    g_Character_2.Set_Clip();
    g_Character_2.x_pos_ = 200;
    g_Character_2.y_pos_ = 200;

    g_Character_3.LoadImg("player_right.png", g_Screen);
    g_Character_3.Set_Clip();
    g_Character_3.x_pos_ = 400;
    g_Character_3.y_pos_ = 600;

    g_Character_4.LoadImg("player_right.png", g_Screen);
    g_Character_4.Set_Clip();
    g_Character_4.x_pos_ = 400;
    g_Character_4.y_pos_ = 200;

    g_Ball.LoadImg("ball.png", g_Screen);
    g_Ball.x_pos_ = 300;
    g_Ball.y_pos_ = 400;

    

    bool isquit = false;
    int is_chance = 0;

    while(!isquit)
    {
        fps.start();
        while(SDL_PollEvent(&g_Event))
        {
            if(g_Event.type == SDL_QUIT)
            {
                isquit = true;
            }
            if(g_Event.type == SDL_KEYDOWN)
            {
                if(g_Event.key.keysym.sym == SDLK_c)
                {
                    if(is_chances == 1)
                    {
                        is_chances = 0;
                    }
                    else{
                        is_chances = 1;
                    }
                    std::cout<<"c"<<std::endl;
                    std::cout<<is_chance<<std::endl;
                }
                if(g_Event.key.keysym.sym == SDLK_q)
                {
                    if(is_chances_1 == 1)
                    {
                        is_chances_1 = 0;
                    }
                    else{
                        is_chances_1 = 1;
                    }
                    std::cout<<"q"<<std::endl;
                    std::cout<<is_chances_1<<std::endl;
                }
            }
            if(is_chances == 0)
            {
                g_Character_1.HandleInputAction_1(g_Event,g_Screen);
            }
            else{
                g_Character_3.HandleInputAction_1(g_Event,g_Screen);
            }

            if(is_chances_1 == 0)
            {
                g_Character_2.HandleInputAction_2(g_Event,g_Screen);
            }
            else{
                g_Character_4.HandleInputAction_2(g_Event,g_Screen);
            }
        }
        SDL_RenderClear(g_Screen);
        // SDL_SetRenderDrawColor(g_Screen,255,255,255,255);
        g_BackGround.Render(g_Screen,NULL);
        // renderText(g_Screen, 100, 100 , 100, 100, "FreeSans.ttf", 30,  255, 25, 25, 255, "hello ttf");
        if(is_chances == 1)
        {
            AutoMove(&g_Character_1);
        }
        else{
            AutoMove(&g_Character_3);
        }

        if(is_chances_1 == 1)
        {
            AutoMove(&g_Character_2);
        }
        else{
            AutoMove(&g_Character_4);
        }
        g_Character_1.Show(g_Screen);
        g_Character_2.Show(g_Screen);
        g_Character_3.Show(g_Screen);
        g_Character_4.Show(g_Screen);
        g_Ball.Show(g_Screen);
        g_Character_1.Center();
        g_Character_2.Center();
        g_Character_3.Center();
        g_Character_4.Center();
        g_Ball.Center();
        Force();
        if(g_Ball.is_move_ == true) BallMove();

        

        SDL_RenderPresent(g_Screen);
        int real_time = fps.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND ;//ms
        
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            std::cout<<delay_time<<std::endl;
            if(delay_time >=0) SDL_Delay(delay_time);
        }
    }

    Close();
    return 0;
   
}