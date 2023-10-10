#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include "common.h"
#include <cstdlib>
#include <cmath>
#include "base_object.h"
#include "Player_Object.h"
#include "Ball_Object.h"
#include "ImpTimer.h"

BaseObject g_BackGround;
BaseObject g_Goal_BackGround;
BaseObject g_Setting;

BaseObject Cup;

BaseObject Setting_Home_Bnt;
BaseObject Setting_Continute_Bnt;
BaseObject Setting_Quit_Bnt;
BaseObject Setting_SoundOn_Bnt;
BaseObject Setting_SoundOff_Bnt;
BaseObject Finish_Score;

BaseObject g_GUI;

BaseObject g_Finish_Option;

BaseObject Button1;
BaseObject Button2;

BaseObject g_Score_BackGround;
BaseObject Time_Break_Skill;
BaseObject Magic_Skill;
BaseObject Run;
BaseObject Run1;

PlayerObject g_Goal_frame;
PlayerObject g_Goal_frame1;
PlayerObject g_Character_1;
PlayerObject g_Character_2;
PlayerObject g_Character_3;
PlayerObject g_Character_4;
BallObject g_Ball;

ImpTimer goal;

ImpTimer fps;
ImpTimer finish;

struct BreakTime {
    // std::string name;
    float x_C1;
    float x_C2;
    float y_C1;
    float y_C2;
    float x_Ball;
    float y_Ball;
    int scoreBlue;
    int scoreRed;

};

std::vector<BreakTime> Data_List; // Tạo một vector để lưu trữ danh sách các cấu trúc vị trí 

int is_chances = 0;
int is_chances_1 = 0;
bool is_goal = false;
bool start_flag = false;
int sizeList = 0;

int score_blue= 0;
int score_red = 0;

int count = 0;
int list[5];


bool isquit = false;
bool is_skill = false;
bool is_skill_1 = false;
int is_chance = 0;
int time = 0;
int count_goal =0;
int count_skill =0;
int time_pass = 0;
bool finish_option = false;
int score_flag = 0;
std::string text1 ="";
std::string text2 ="";
std::string text3 ="";
std::string text4 ="";
std::string score1 ="";
std::string score2 ="";

int setting_flag = 0;
// int music_control = 0;

// Mix_Chunk *music2 = Mix_LoadWAV("sounds/ballbouncing.wav");

bool InitData()
{
  bool success = true;
  int ret = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
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
    bool ret = g_BackGround.LoadImage("assets/Play_mode/football_turf.png",g_Screen,0,0);

    if(ret == false)
    {
        return false;
    }
    return true;
}

// bool LoadGoal()
// {
//     bool ret = g_Goal_BackGround.LoadImage("celebrate/spritesheet.png",g_Screen);
//     g_Goal_BackGround.Set_Clip2();
//     g_Goal_BackGround.x_pos_ =0;
//     g_Goal_BackGround.y_pos_ = 100;

//     if(ret == false)
//     {
//         return false;
//     }
//     return true;
// }

bool LoadGoalFrame()
{
    bool ret = g_Goal_frame.LoadImage("assets/Goal/spritesheet.png",g_Screen, 0,0);

    if(ret == false)
    {
        return false;
    }
    return true;
}


bool LoadScore()
{
    bool ret = g_Score_BackGround.LoadImage("assets/Main_menu/score_table.png",g_Screen,160,100);

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

// void AutoMove(PlayerObject *g_Character_ , int Case , int team )
// {
//     // std::cout<<g_Character_->x_pos_<<std::endl;
//     // std::cout<<g_Character_->y_pos_<<std::endl;
//     // trả input về 0 mỗi lần di chuyển xong
//     if( Case == 0 && team == 0)
//     {
//         if(g_Character_->x_pos_ != 400 || g_Character_->y_pos_ != 300){
//             // if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 250)
//             // {
//                 if(g_Character_->x_pos_ > 400)
//                 {
//                     g_Character_->status = 1;
//                     g_Character_->input_type.left = 1;
//                 }
//                 if(g_Character_->x_pos_ < 400)
//                 {
//                     // g_Character_->y_pos_ +=5;
//                     g_Character_->status = 0;
//                     g_Character_->input_type.right = 1;
//                 }
//                 if(g_Character_->y_pos_ > 300)
//                 {
//                     // g_Character_->x_pos_ -=5;
//                     g_Character_->status = 2;
//                     g_Character_->input_type.up = 1;
//                 }
//                 if(g_Character_->y_pos_ < 300)
//                 {
//                     // g_Character_->y_pos_ -=5;
//                     g_Character_->status = 3;
//                     g_Character_->input_type.down = 1;
//                 }
//         }   
//         else{
//             g_Character_->status = 0;
//             g_Character_->input_type.left = 0;
//             g_Character_->input_type.right = 0;
//             g_Character_->input_type.up = 0;
//             g_Character_->input_type.down = 0;
//         }       
//     }

//     if(Case == 1 && team == 0)
//     {
//         if(g_Character_->x_pos_ != 400 || g_Character_->y_pos_ != 300){
//             // if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 250)
//             // {
//                 if(g_Character_->x_pos_ > 200)
//                 {
//                     g_Character_->status = 1;
//                     g_Character_->input_type.left = 1;
//                 }
//                 if(g_Character_->x_pos_ < 200)
//                 {
//                     // g_Character_->y_pos_ +=5;
//                     g_Character_->status = 0;
//                     g_Character_->input_type.right = 1;
//                 }
//                 if(g_Character_->y_pos_ > 300)
//                 {
//                     // g_Character_->x_pos_ -=5;
//                     g_Character_->status = 2;
//                     g_Character_->input_type.up = 1;
//                 }
//                 if(g_Character_->y_pos_ < 300)
//                 {
//                     // g_Character_->y_pos_ -=5;
//                     g_Character_->status = 3;
//                     g_Character_->input_type.down = 1;
//                 }
//         }   
//         else{
//             g_Character_->status = 0;
//             g_Character_->input_type.left = 0;
//             g_Character_->input_type.right = 0;
//             g_Character_->input_type.up = 0;
//             g_Character_->input_type.down = 0;
//         }
//     }

//     if( Case == 0 && team == 1)
//     {
//         if(g_Character_->x_pos_ != 700 || g_Character_->y_pos_ != 300){
//             // if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 250)
//             // {
//                 if(g_Character_->x_pos_ > 700)
//                 {
//                     g_Character_->status = 1;
//                     g_Character_->input_type.left = 1;
//                 }
//                 if(g_Character_->x_pos_ < 700)
//                 {
//                     // g_Character_->y_pos_ +=5;
//                     g_Character_->status = 0;
//                     g_Character_->input_type.right = 1;
//                 }
//                 if(g_Character_->y_pos_ > 300)
//                 {
//                     // g_Character_->x_pos_ -=5;
//                     g_Character_->status = 2;
//                     g_Character_->input_type.up = 1;
//                 }
//                 if(g_Character_->y_pos_ < 300)
//                 {
//                     // g_Character_->y_pos_ -=5;
//                     g_Character_->status = 3;
//                     g_Character_->input_type.down = 1;
//                 }
//         }   
//         else{
//             g_Character_->status = 0;
//             g_Character_->input_type.left = 0;
//             g_Character_->input_type.right = 0;
//             g_Character_->input_type.up = 0;
//             g_Character_->input_type.down = 0;
//         }
        
//     }
//     if(Case == 1 && team == 1)
//     {
//         if(g_Character_->x_pos_ != 500 || g_Character_->y_pos_ != 300){
//             // if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 250)
//             // {
//                 if(g_Character_->x_pos_ > 500)
//                 {
//                     g_Character_->status = 1;
//                     g_Character_->input_type.left = 1;
//                 }
//                 if(g_Character_->x_pos_ < 500)
//                 {
//                     // g_Character_->y_pos_ +=5;
//                     g_Character_->status = 0;
//                     g_Character_->input_type.right = 1;
//                 }
//                 if(g_Character_->y_pos_ > 300)
//                 {
//                     // g_Character_->x_pos_ -=5;
//                     g_Character_->status = 2;
//                     g_Character_->input_type.up = 1;
//                 }
//                 if(g_Character_->y_pos_ < 300)
//                 {
//                     // g_Character_->y_pos_ -=5;
//                     g_Character_->status = 3;
//                     g_Character_->input_type.down = 1;
//                 }
//         }   
//         else{
//             g_Character_->status = 0;
//             g_Character_->input_type.left = 0;
//             g_Character_->input_type.right = 0;
//             g_Character_->input_type.up = 0;
//             g_Character_->input_type.down = 0;
//         }
//     }

// }

void AutoMove(PlayerObject *g_Character_, int team)
{
    // std::cout<<g_Character_->x_pos_<<std::endl;
    // std::cout<<g_Character_->y_pos_<<std::endl;
    // trả input về 0 mỗi lần di chuyển xong
    g_Character_->input_type.right = 0;
    g_Character_->input_type.up = 0;
    g_Character_->input_type.down = 0;
    g_Character_->input_type.left = 0;
    if(team == 0)
    {
        if(g_Character_->x_pos_ >= -10 && g_Character_->x_pos_ + g_Character_->width_frame <= SCREEN_WIDTH + 10 && g_Character_->y_pos_ >= -10 && g_Character_->y_pos_ + g_Character_->height_frame <= SCREEN_HEIGHT + 10){
            if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 100 && g_Ball.x_center < 450)
            {
                if(g_Ball.x_center > g_Character_->x_center)
                {
                    // g_Character_->x_pos_ += 5;
                    g_Character_->input_type.right = 1;
                }
                if(g_Ball.y_center > g_Character_->y_center)
                {
                    // g_Character_->y_pos_ +=5;
                    g_Character_->input_type.down = 1;
                }
                if(g_Ball.x_center < g_Character_->x_center)
                {
                    // g_Character_->x_pos_ -=5;
                    g_Character_->input_type.left = 1;
                }
                if(g_Ball.y_center < g_Character_->y_center)
                {
                    // g_Character_->y_pos_ -=5;
                    g_Character_->input_type.up = 1;
                }
            }
            else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 100 && g_Ball.x_center >= 450)
            {
                if(g_Character_->x_center > 205)
                {
                    // g_Character_->x_pos_ += 5;

                    g_Character_->input_type.left = 1;
                }
                if(g_Character_->y_center > 350)
                {
                    // g_Character_->y_pos_ +=5;

                    g_Character_->input_type.up = 1;
                }
                if(g_Character_->y_center < 330 )
                {
                    // g_Character_->x_pos_ -=5;

                    g_Character_->input_type.down = 1;
                }
                if(g_Character_->x_center <= 205 && g_Character_->y_center <= 350 && g_Character_->y_center >= 330)
                {
                    g_Character_->input_type.left = 0;
                    g_Character_->input_type.right = 0;
                    g_Character_->input_type.up = 0;
                    g_Character_->input_type.down = 0;
                }
            }
            else{
                g_Character_->input_type.left = 0;
                g_Character_->input_type.right = 0;
                g_Character_->input_type.up = 0;
                g_Character_->input_type.down = 0;
            }
        }

    }
    if(team == 1)
    {
        if(g_Character_->x_pos_ >= -10 && g_Character_->x_pos_ + g_Character_->width_frame <= SCREEN_WIDTH + 10 && g_Character_->y_pos_ >= -10 && g_Character_->y_pos_ + g_Character_->height_frame <= SCREEN_HEIGHT + 10){
            if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 100 && g_Ball.x_center >= 450)
            {
                if(g_Ball.x_center > g_Character_->x_center)
                {
                    // g_Character_->x_pos_ += 5;
                    g_Character_->input_type.right = 1;
                }
                if(g_Ball.y_center > g_Character_->y_center)
                {
                    // g_Character_->y_pos_ +=5;
                    g_Character_->input_type.down = 1;
                }
                if(g_Ball.x_center < g_Character_->x_center)
                {
                    // g_Character_->x_pos_ -=5;
                    g_Character_->input_type.left = 1;
                }
                if(g_Ball.y_center < g_Character_->y_center)
                {
                    // g_Character_->y_pos_ -=5;
                    g_Character_->input_type.up = 1;
                }
            }
            else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2)) > 100 && g_Ball.x_center < 450)
            {
                if(g_Character_->x_center < 680)
                {
                    // g_Character_->x_pos_ += 5;

                    g_Character_->input_type.right = 1;
                }
                if(g_Character_->y_center > 350)
                {
                    // g_Character_->y_pos_ +=5;

                    g_Character_->input_type.up = 1;
                }
                if(g_Character_->y_center < 330 )
                {
                    // g_Character_->x_pos_ -=5;

                    g_Character_->input_type.down = 1;
                }
                if(g_Character_->x_center >= 680 && g_Character_->y_center <= 350 && g_Character_->y_center >= 330)
                {
                    g_Character_->input_type.left = 0;
                    g_Character_->input_type.right = 0;
                    g_Character_->input_type.up = 0;
                    g_Character_->input_type.down = 0;
                }
            }
            else{
                g_Character_->input_type.left = 0;
                g_Character_->input_type.right = 0;
                g_Character_->input_type.up = 0;
                g_Character_->input_type.down = 0;
            }
        }

    }
   
}

void Music()
{
    Mix_Music *music = Mix_LoadMUS("sounds/theme.mp3");
    if (music == nullptr) {
        SDL_Log("Không thể tải âm thanh: %s", Mix_GetError());
    }
    Mix_PlayMusic(music, 20);
}

void Sound_Ball()
{
    Mix_Chunk *music2 = Mix_LoadWAV("sounds/ballkick.wav");
    if(music2 == nullptr){
        SDL_Log("Không thể tải âm thanh: %s", Mix_GetError());
    }
    Mix_PlayChannel(1, music2, 0);
}

void angle(PlayerObject *g_Character_)
{
    float x = std::abs(g_Ball.x_center -g_Character_->x_center);
    // std::cout<<g_Ball.x_center<<" "<< g_Ball.y_center<<" "<<g_Character_1.x_center<<" "<< g_Character_1.y_center<<std::endl;
    float v = sqrt(pow(std::abs(g_Ball.x_center -g_Character_->x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_->y_center),2));

    g_Ball.angle = std::acos(x / v);

    g_Ball.angle = g_Ball.angle * 180.0 / M_PI;
    if(sound_control == 0) Sound_Ball();

    // Mix_PlayChannel(1, music2, 0);
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
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_3.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_3.y_center),2)) < 60 && g_Ball.Force == 0 && State != SINGPLEPLAYER_MODE)
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
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_3.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_3.y_center),2)) < 60 && g_Ball.Force != 0 && State != SINGPLEPLAYER_MODE)
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
     else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_4.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_4.y_center),2)) < 60 && g_Ball.Force == 0 && State != SINGPLEPLAYER_MODE)
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
    else if(sqrt(pow(std::abs(g_Ball.x_center -g_Character_4.x_center),2)+pow(std::abs(g_Ball.y_center -g_Character_4.y_center),2)) < 60 && g_Ball.Force != 0 && State != SINGPLEPLAYER_MODE)
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

    if(g_Ball.x_pos_ >= SCREEN_WIDTH_YARD_S -10 && g_Ball.x_pos_<= SCREEN_WIDTH_YARD_S + 10  && g_Ball.Force != 0)
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
    else if(g_Ball.x_pos_ + g_Ball.width_frame <=SCREEN_WIDTH_YARD_M + 10 && g_Ball.x_pos_ + g_Ball.width_frame >=SCREEN_WIDTH_YARD_M - 10  && g_Ball.Force != 0)
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
    else if(g_Ball.y_pos_ >= SCREEN_HEIGHT_YARD_S -10 && g_Ball.y_pos_ <= SCREEN_HEIGHT_YARD_S + 10  && g_Ball.Force != 0)
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
    else if(g_Ball.y_pos_ + g_Ball.height_frame <=SCREEN_HEIGHT_YARD_M + 10 && g_Ball.y_pos_ + g_Ball.height_frame >=SCREEN_HEIGHT_YARD_M - 10   && g_Ball.Force != 0)
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
        if(g_Ball.x_pos_ < SCREEN_WIDTH_YARD_S -10) g_Ball.x_pos_ +=5;
        if(g_Ball.y_pos_ < SCREEN_HEIGHT_YARD_S -10) g_Ball.y_pos_ +=5;
        if(g_Ball.x_pos_ + g_Ball.width_frame > SCREEN_WIDTH_YARD_M + 10) g_Ball.x_pos_ -=5;
        if(g_Ball.y_pos_ + g_Ball.height_frame > SCREEN_HEIGHT_YARD_M + 10) g_Ball.y_pos_ -=5;
    }

}

void BallMove()
{
    if(g_Ball.corner == 1)
    {
        if(g_Ball.Force > 0)
        {
            if(g_Ball.x_pos_ >= SCREEN_WIDTH_YARD_S) g_Ball.x_pos_ -= (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ >= SCREEN_HEIGHT_YARD_S) g_Ball.y_pos_ -= (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
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
            if(g_Ball.x_pos_ + g_Ball.width_frame <= SCREEN_WIDTH_YARD_M) g_Ball.x_pos_ += (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ >= SCREEN_HEIGHT_YARD_S) g_Ball.y_pos_ -= (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
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
            if(g_Ball.x_pos_ + g_Ball.width_frame <= SCREEN_WIDTH_YARD_M) g_Ball.x_pos_ += (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ + g_Ball.height_frame <= SCREEN_HEIGHT_YARD_M) g_Ball.y_pos_ += (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
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
            if(g_Ball.x_pos_ >= SCREEN_WIDTH_YARD_S) g_Ball.x_pos_ -= (100 /5)*std::cos(g_Ball.angle* M_PI / 180.0);
            if(g_Ball.y_pos_ + g_Ball.height_frame <= SCREEN_HEIGHT_YARD_M) g_Ball.y_pos_ += (100 /5)*std::sin(g_Ball.angle* M_PI / 180.0);
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

void Goal()
{
    if(g_Ball.x_center > 100 && g_Ball.x_center < 130 && g_Ball.y_center > 310 && g_Ball.y_center < 390)
    {
        is_goal = true;
        score_red += 1;
        score_flag = 2;
        goal.start();
    }
    if(g_Ball.x_center > 770 && g_Ball.x_center < 800 && g_Ball.y_center > 310 && g_Ball.y_center < 390)
    {
        is_goal = true;
        score_blue += 1;
        score_flag = 1;
        goal.start();
    }
}

void Time_breakthrough()
{
    BreakTime Time1 = {g_Character_1.x_pos_,g_Character_2.x_pos_,g_Character_1.y_pos_,g_Character_2.y_pos_,g_Ball.x_pos_,g_Ball.y_pos_,score_blue,score_red};
    Data_List.push_back(Time1);
    sizeList++;
    if(sizeList > 5)
    {
        Data_List.erase(Data_List.begin());
    }
}
void Run_Skill()
{
    g_Character_1.x_pos_ = Data_List[0].x_C1;
    g_Character_2.x_pos_ = Data_List[0].x_C2;
    g_Character_1.y_pos_ = Data_List[0].y_C1;
    g_Character_2.y_pos_ = Data_List[0].y_C2;
    g_Ball.x_pos_ = Data_List[0].x_Ball;
    g_Ball.y_pos_ = Data_List[0].y_Ball;
    score_blue = Data_List[0].scoreBlue;
    score_red = Data_List[0].scoreRed;

}

void Run_Skill_1()
{

}

void Single_Player()
{
   if(!start_flag) 
    {
        finish.start();
        start_flag = true;
        g_Character_1.x_pos_ = 360;
        g_Character_1.y_pos_ = 325;
        g_Character_2.x_pos_ = 540;
        g_Character_2.y_pos_ = 325;
        g_Ball.x_pos_ = 420;
        g_Ball.y_pos_ = 320;
        score_blue = 0;
        score_red = 0;
    }
    // g_Score_BackGround.Render_Score(g_Screen,NULL);
    g_GUI.Render(g_Screen,NULL);

    renderText(g_Screen, 770, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text1.c_str());
    renderText(g_Screen, 785, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text2.c_str());
    // renderText(g_Screen, 170, 110 , 30, 30, "FreeSans.ttf", 20,  255, 25, 25, 255, ":");
    renderText(g_Screen, 815, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text3.c_str());
    renderText(g_Screen, 830, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text4.c_str());

    renderText(g_Screen, 400, 30 , 30, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, score1.c_str());
    renderText(g_Screen, 480, 30 , 30, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, score2.c_str());


    g_Character_1.Show(g_Screen);
    g_Character_2.Show(g_Screen);
    // g_Goal_BackGround.Show2(g_Screen);
    // g_Character_3.Show(g_Screen);
    // g_Character_4.Show(g_Screen);
    g_Ball.Show(g_Screen);

    if(setting_flag == 1)
    {
        g_Setting.Render(g_Screen,NULL);
        Setting_Home_Bnt.Render(g_Screen,NULL);
        Setting_Continute_Bnt.Render(g_Screen,NULL);
        Setting_Quit_Bnt.Render(g_Screen,NULL);
        if(sound_control == 0) Setting_SoundOn_Bnt.Render(g_Screen,NULL);
        if(sound_control == 1) Setting_SoundOff_Bnt.Render(g_Screen,NULL);
    }

    if(finish_option)
    {
        g_Finish_Option.Render(g_Screen);
        Button1.Render(g_Screen);
        Button2.Render(g_Screen);
        Finish_Score.Render(g_Screen);
        Cup.Render(g_Screen);
        // if(score_blue > score_red)
        // {
        //     renderText(g_Screen, 500, 200 , 30, 30, "FreeSans.ttf", 30,  255, 25, 25, 255, "Blue Team Win");
        // }
        // else if(score_blue > score_red)
        // {
        //     renderText(g_Screen, 500, 200 , 30, 30, "FreeSans.ttf", 30,  255, 25, 25, 255, "Red Team Win");
        // }
        // else{
        //     renderText(g_Screen, 520, 200 , 80, 80, "FreeSans.ttf", 80,  255, 25, 25, 255, "Draw !!!");
        // }
        renderText(g_Screen, 530, 285 , 20, 40, "FreeSans.ttf", 40,  255, 25, 25, 255, std::to_string(score_blue).c_str());
        // renderText(g_Screen, 540, 280 , 20, 40, "FreeSans.ttf", 40,  255, 25, 25, 255, ":");
        renderText(g_Screen, 560, 285 , 20, 40, "FreeSans.ttf", 40,  255, 25, 25, 255, std::to_string(score_red).c_str());

    } 
    
    if(is_goal)
    {
        // g_Goal_BackGround.LoadImage(g_Goal_BackGround.list[count_goal].c_str(),g_Screen,0,0);
        if(score_flag == 1) g_Goal_BackGround.LoadImage("assets/Play_mode copy/goal_banner_blue_team.png",g_Screen,0,0);
        if(score_flag == 2) g_Goal_BackGround.LoadImage("assets/Play_mode copy/goal_banner_red_team.png",g_Screen,0,0);
        g_Goal_BackGround.rect_.x = 0;
        g_Goal_BackGround.rect_.y = 100;
        g_Goal_BackGround.Render(g_Screen,NULL);
        // if(count_goal >= 25)
        // {
        //     count_goal = 0;
        // }
        // count_goal++;
        if(goal.get_ticks() >= 1000)
        {
            is_goal = false;
            g_Character_1.x_pos_ = 360;
            g_Character_1.y_pos_ = 300;

            g_Character_2.x_pos_ = 540;
            g_Character_2.y_pos_ = 300;

            // g_Character_3.x_pos_ = 360;
            // g_Character_3.y_pos_ = 500;

            // g_Character_4.x_pos_ = 540;
            // g_Character_4.y_pos_ = 500;
            g_Ball.x_pos_ = 420;
            g_Ball.y_pos_ = 300;
        }
    }
    g_Character_1.Center();
    g_Character_2.Center();
    // g_Character_3.Center();
    // g_Character_4.Center();
    g_Ball.Center();
    Force();
    if(!is_goal) Goal();
    if(g_Ball.is_move_ == true) BallMove();
}

void Multi_Player()
{
    if(!start_flag) 
    {
        finish.start();
        start_flag = true;
        g_Character_1.x_pos_ = 360;
        g_Character_1.y_pos_ = 325;
        g_Character_2.x_pos_ = 540;
        g_Character_2.y_pos_ = 325;
        g_Ball.x_pos_ = 420;
        g_Ball.y_pos_ = 320;
        score_blue = 0;
        score_red = 0;
    }
    // g_Score_BackGround.Render_Score(g_Screen,NULL);
    g_GUI.Render(g_Screen,NULL);

    renderText(g_Screen, 770, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text1.c_str());
    renderText(g_Screen, 785, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text2.c_str());
    // renderText(g_Screen, 170, 110 , 30, 30, "FreeSans.ttf", 20,  255, 25, 25, 255, ":");
    renderText(g_Screen, 815, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text3.c_str());
    renderText(g_Screen, 830, 30 , 10, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, text4.c_str());

    renderText(g_Screen, 400, 30 , 30, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, score1.c_str());
    renderText(g_Screen, 480, 30 , 30, 30, "FreeSans.ttf", 80,  0, 0, 0, 255, score2.c_str());

    // Run.rect_.x = g_Character_3.x_pos_;
    // Run.rect_.y = g_Character_3.y_pos_+30;

    // Run1.rect_.x = g_Character_4.x_pos_;
    // Run1.rect_.y = g_Character_4.y_pos_+30;

    if(is_chances == 1)
    {
        AutoMove(&g_Character_1,0);
        Run.rect_.x = g_Character_3.x_pos_ - 20;
        Run.rect_.y = g_Character_3.y_pos_;
    }
    else{
        AutoMove(&g_Character_3,0);
        Run.rect_.x = g_Character_1.x_pos_- 20;
        Run.rect_.y = g_Character_1.y_pos_;
    }

    if(is_chances_1 == 1)
    {
        AutoMove(&g_Character_2,1);
        Run1.rect_.x = g_Character_4.x_pos_- 20;
        Run1.rect_.y = g_Character_4.y_pos_;
    }
    else{
        AutoMove(&g_Character_4,1);
        Run1.rect_.x = g_Character_2.x_pos_- 20;
        Run1.rect_.y = g_Character_2.y_pos_;
    }

    Run.Render(g_Screen,NULL);
    Run1.Render(g_Screen,NULL);

    g_Character_1.Show(g_Screen);
    g_Character_2.Show(g_Screen);
    // g_Goal_BackGround.Show2(g_Screen);
    g_Character_3.Show(g_Screen);
    g_Character_4.Show(g_Screen);

    g_Ball.Show(g_Screen);

    if(setting_flag == 1)
    {
        g_Setting.Render(g_Screen,NULL);
        Setting_Home_Bnt.Render(g_Screen,NULL);
        Setting_Continute_Bnt.Render(g_Screen,NULL);
        Setting_Quit_Bnt.Render(g_Screen,NULL);
        if(sound_control == 0) Setting_SoundOn_Bnt.Render(g_Screen,NULL);
        if(sound_control == 1) Setting_SoundOff_Bnt.Render(g_Screen,NULL);
    }

    if(finish_option)
    {
        g_Finish_Option.Render(g_Screen);
        Button1.Render(g_Screen);
        Button2.Render(g_Screen);
        Finish_Score.Render(g_Screen);
        Cup.Render(g_Screen);
        // if(score_blue > score_red)
        // {
        //     renderText(g_Screen, 500, 200 , 30, 30, "FreeSans.ttf", 30,  255, 25, 25, 255, "Blue Team Win");
        // }
        // else if(score_blue > score_red)
        // {
        //     renderText(g_Screen, 500, 200 , 30, 30, "FreeSans.ttf", 30,  255, 25, 25, 255, "Red Team Win");
        // }
        // else{
        //     renderText(g_Screen, 520, 200 , 80, 80, "FreeSans.ttf", 80,  255, 25, 25, 255, "Draw !!!");
        // }
        renderText(g_Screen, 530, 285 , 20, 40, "FreeSans.ttf", 40,  255, 25, 25, 255, std::to_string(score_blue).c_str());
        // renderText(g_Screen, 540, 280 , 20, 40, "FreeSans.ttf", 40,  255, 25, 25, 255, ":");
        renderText(g_Screen, 560, 285 , 20, 40, "FreeSans.ttf", 40,  255, 25, 25, 255, std::to_string(score_red).c_str());

    } 
    

    if(is_goal)
    {
        // g_Goal_BackGround.LoadImage(g_Goal_BackGround.list[count_goal].c_str(),g_Screen,0,0);
        if(score_flag == 1) g_Goal_BackGround.LoadImage("assets/Play_mode copy/goal_banner_blue_team.png",g_Screen,0,0);
        if(score_flag == 2) g_Goal_BackGround.LoadImage("assets/Play_mode copy/goal_banner_red_team.png",g_Screen,0,0);
        g_Goal_BackGround.rect_.x = 0;
        g_Goal_BackGround.rect_.y = 100;
        g_Goal_BackGround.Render(g_Screen,NULL);
        // if(count_goal >= 25)
        // {
        //     count_goal = 0;
        // }
        // count_goal++;
        if(goal.get_ticks() >= 1000)
        {
            is_goal = false;
            g_Character_1.x_pos_ = 360;
            g_Character_1.y_pos_ = 300;

            g_Character_2.x_pos_ = 540;
            g_Character_2.y_pos_ = 300;

            g_Character_3.x_pos_ = 200;
            g_Character_3.y_pos_ = 300;

            g_Character_4.x_pos_ = 700;
            g_Character_4.y_pos_ = 300;
            g_Ball.x_pos_ = 420;
            g_Ball.y_pos_ = 300;
        }
    }
    g_Character_1.Center();
    g_Character_2.Center();
    g_Character_3.Center();
    g_Character_4.Center();
    g_Ball.Center();
    Force();
    if(!is_goal) Goal();
    if(g_Ball.is_move_ == true) BallMove();
}

int main( int argc, char *argv[] )
{
    // ImpTimer fps;
    // ImpTimer finish;
    if(InitData() == false)
    {
        return -1;
    }

    if(LoadBackGround() == false)
    {
        return -1;
    }

    if(LoadScore() == false)
    {
        return -1;
    }
    if(g_Menu.LoadMenu() == false)
    {
        return -1;
    }

    int flag = 0;

    if (TTF_Init() == -1) {
        SDL_Log("Unable to initialize TTF: %s", TTF_GetError());
        SDL_DestroyRenderer(g_Screen);
        SDL_DestroyWindow(g_Window);
        SDL_Quit();
        return 1;
    }



    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout<<"fail"<<std::endl;
    }

    // Load và phát nhạc nền
    Mix_Music *music = Mix_LoadMUS("sounds/theme.mp3");
    if (music == nullptr) {
        SDL_Log("Không thể tải âm thanh: %s", Mix_GetError());
    }
    Mix_PlayMusic(music, 20);
    
    
    Cup.LoadImage("assets/Main_menu/hehe-removebg-preview.png",g_Screen,250,120);
    Cup.rect_.x = 430;
    Cup.rect_.y = 180;
    
    Finish_Score.LoadImage("assets/Main_menu/finish_score-removebg-preview.png",g_Screen,200,50);
    Finish_Score.rect_.x = 450;
    Finish_Score.rect_.y = 280;

    Setting_Home_Bnt.LoadImage("assets/common_btns/Back_to_home_btn.png",g_Screen,100,40);
    Setting_Home_Bnt.rect_.x = 400;
    Setting_Home_Bnt.rect_.y = 200;

    Setting_Continute_Bnt.LoadImage("assets/common_btns/Continute_btn.png",g_Screen,100,40);
    Setting_Continute_Bnt.rect_.x = 400;
    Setting_Continute_Bnt.rect_.y = 300;

    Setting_Quit_Bnt.LoadImage("assets/common_btns/Quit_btn.png",g_Screen,100,40);
    Setting_Quit_Bnt.rect_.x = 400;
    Setting_Quit_Bnt.rect_.y = 400;

    Setting_SoundOn_Bnt.LoadImage("assets/common_btns/Sound_on.png",g_Screen,100,40);
    Setting_SoundOn_Bnt.rect_.x = 400;
    Setting_SoundOn_Bnt.rect_.y = 550;

    Setting_SoundOff_Bnt.LoadImage("assets/common_btns/Sound_off.png",g_Screen,100,40);
    Setting_SoundOff_Bnt.rect_.x = 400;
    Setting_SoundOff_Bnt.rect_.y = 550;
    

    g_Finish_Option.LoadImage("assets/Main_menu/menu_background.png",g_Screen,400,300);
    g_Finish_Option.rect_.x = 250;
    g_Finish_Option.rect_.y = 175;

    g_GUI.LoadImage("assets/Play_mode copy/GUI.png",g_Screen,900,700);
    g_GUI.rect_.x = 0;
    g_GUI.rect_.y = 0;

    g_Setting.LoadImage("assets/common_btns/pop_up.png",g_Screen,0,0);
    g_Setting.rect_.x = 200;
    g_Setting.rect_.y = 50;

    Button1.LoadImage("assets/Main_menu/Resume_btn.png",g_Screen,100,30);
    Button1.rect_.x = 500;
    Button1.rect_.y = 350;

    Button2.LoadImage("assets/Main_menu/Home_btn.png",g_Screen,100,30);
    Button2.rect_.x = 500;
    Button2.rect_.y = 400;

    g_Goal_BackGround.SetClip();
    g_Goal_BackGround.rect_.x = 200;
    g_Goal_BackGround.rect_.y = 150;

    Time_Break_Skill.SetClip1();
    Time_Break_Skill.rect_.x = 0;
    Time_Break_Skill.rect_.y = 0;

    Magic_Skill.SetClip2();
    Magic_Skill.rect_.x = 0;
    Magic_Skill.rect_.y = 0;

    g_Goal_frame.LoadImg1("assets/Goal/spritesheet.png",g_Screen);
    g_Goal_frame.Set_Clip1();
    g_Goal_frame.x_pos_ = 50;
    g_Goal_frame.y_pos_ = 310;

    g_Goal_frame1.LoadImg1("assets/Goal/spritesheet.png",g_Screen);
    g_Goal_frame1.Set_Clip1();
    g_Goal_frame1.x_pos_ = 700;
    g_Goal_frame1.y_pos_ = 310;

    g_Character_1.LoadImg("assets/animation/player_run/blue_team/blue_stand.png", g_Screen);
    g_Character_1.Set_Clip();
    g_Character_1.x_pos_ = 360;
    g_Character_1.y_pos_ = 300;

    Run.LoadImage("assets/Main_menu/run2.png", g_Screen,60,60);


    Run1.LoadImage("assets/Main_menu/run2.png", g_Screen,60,60);


    g_Character_2.LoadImg("assets/animation/player_run/red_team/red_stand.png", g_Screen);
    g_Character_2.Set_Clip();
    g_Character_2.x_pos_ = 540;
    g_Character_2.y_pos_ = 300;

    g_Character_3.LoadImg("assets/animation/player_run/blue_team/blue_stand.png", g_Screen);
    g_Character_3.Set_Clip();
    g_Character_3.x_pos_ = 200;
    g_Character_3.y_pos_ = 300;

    g_Character_4.LoadImg("assets/animation/player_run/red_team/red_stand.png", g_Screen);
    g_Character_4.Set_Clip();
    g_Character_4.x_pos_ = 700;
    g_Character_4.y_pos_ = 300;


    g_Ball.LoadImg("assets/Play_mode/ball.png", g_Screen);
    g_Ball.x_pos_ = 420;
    g_Ball.y_pos_ = 300;


    // finish.start();

    while(!isquit)
    {
        fps.start();
        if(music_control == 1)
        {
            Mix_PauseMusic();
        }
        else{
            Mix_ResumeMusic();
        }
        // Mix_PlayMusic(backgroundMusic, -1);  // -1 để phát lại liên tục
        if(finish.get_ticks()/1000 >= 90)
        {
            finish.stop();
            score_blue = 0;
            score_red = 0;
            finish_option = true;
        }

        //get time finish 
        text1 = std::to_string(finish.get_ticks()/10000);

        if(count != finish.get_ticks()/1000)
        {
            count = finish.get_ticks()/1000;
            Time_breakthrough();
        } 
        
        text2 = std::to_string((finish.get_ticks()%10000)/1000);
        text3 = std::to_string(((finish.get_ticks()%10000)%1000)/100);
        text4 = std::to_string((((finish.get_ticks()%10000)%1000)%100)/10);

        score1 = std::to_string(score_blue);
        score2 = std::to_string(score_red);


        if(SDL_PollEvent(&g_Event))
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
                }
                if(g_Event.key.keysym.sym == SDLK_r)
                {
                    
                    std::cout<<"r"<<std::endl;
                    finish.pause();
                    time_pass = finish.get_ticks();
                    is_skill = true;
                    // Run_Skill();
                    // std::cout<<is_chance<<std::endl;
                }
                if(g_Event.key.keysym.sym == SDLK_p)
                {
                    finish.pause();
                    time_pass = finish.get_ticks();
                    is_skill_1 = true;
                }
            }
            
            if (g_Event.type == SDL_MOUSEBUTTONDOWN) {
                if (g_Event.button.button == SDL_BUTTON_LEFT) {
                    // Xử lý sự kiện nhấp chuột trái ở đây
                    int x = g_Event.button.x;
                    int y = g_Event.button.y;

                    if(setting_flag == 1)
                    {
                        if(x > 400 && x < 500 && y > 200 && y < 240)
                        {
                            currentGameStatus = MENU_MODE;
                            previousGameStatus = START_MODE;
                            if(g_Menu.LoadMenu() == false)
                            {
                                return -1;
                            }
                            // finish_option = false;
                            setting_flag = 0;
                            start_flag = false;
                            flag = 0;
                        }
                        if(x > 400 && x < 500 && y > 300 && y < 340)
                        {
                            setting_flag = 0;
                            finish.unpause();
                        }
                        if(x > 400 && x < 500 && y > 400 && y < 440)
                        {                          
                            isquit = true;
                        }
                        if(x > 400 && x < 500 && y > 500 && y < 600)
                        {
                            if(sound_control == 0)
                            {
                                sound_control = 1;
                            }
                            else{
                                sound_control =0;
                            }
                        }
                    }

                    if(x > 500 && x < 600 && y > 350 && y < 380)                    
                    {
                        finish_option = false;
                        g_Character_1.x_pos_ = 360;
                        g_Character_1.y_pos_ = 325;
                        g_Character_2.x_pos_ = 540;
                        g_Character_2.y_pos_ = 325;
                        g_Ball.x_pos_ = 420;
                        g_Ball.y_pos_ = 320;
                        finish.start();
                    }

                    if(x > 500 && x < 600 && y > 400 && y < 430)                    
                    {
                        flag = 1;
                    }

                    if(x > 50 && x < 100 && y > 20 && y < 70)                    
                    {
                        setting_flag = 1;
                        finish.pause();
                    }
                }
            }

            // g_Menu.RunMenu();
            
            if(State == OPTIONS_MODE)
            {
                if (g_Event.type == SDL_MOUSEBUTTONDOWN) {
                    if (g_Event.button.button == SDL_BUTTON_LEFT) {
                        // Xử lý sự kiện nhấp chuột trái ở đây
                        int x = g_Event.button.x;
                        int y = g_Event.button.y;
                        if(x > 400 && x < 550 && y > 400 && y< 600)
                        {
                            if(music_control == 0)
                            {
                                music_control = 1;
                            }
                            else{
                                music_control = 0;
                            }
                        }
                        if(x > 50 && x < 150 && y > 600 && y < 650)
                        {
                            currentGameStatus = MENU_MODE;
                            previousGameStatus = START_MODE;
                            if(g_Menu.LoadMenu() == false)
                            {
                                return -1;
                            }
                        }
                    }
                }
                
            }
            if(State == MULTIPLAYER_MODE)
            {
                if(is_chances == 0)
                {
                    g_Character_1.HandleInputAction_2(g_Event,g_Screen);
                }
                else{
                    g_Character_3.HandleInputAction_2(g_Event,g_Screen);
                }

                if(is_chances_1 == 0)
                {
                    g_Character_2.HandleInputAction_1(g_Event,g_Screen);
                }
                else{
                    g_Character_4.HandleInputAction_1(g_Event,g_Screen);
                }

            }
            if(State == SINGPLEPLAYER_MODE)
            {
                g_Character_1.HandleInputAction_2(g_Event,g_Screen);
                g_Character_2.HandleInputAction_1(g_Event,g_Screen);
            }

            if(State == CREDITS_MODE)
            {
                if (g_Event.type == SDL_MOUSEBUTTONDOWN) {
                    if (g_Event.button.button == SDL_BUTTON_LEFT) {
                        // Xử lý sự kiện nhấp chuột trái ở đây
                        int x = g_Event.button.x;
                        int y = g_Event.button.y;
                        if(x > 50 && x < 150 && y > 600 && y < 650)
                        {
                            currentGameStatus = MENU_MODE;
                            previousGameStatus = START_MODE;
                            if(g_Menu.LoadMenu() == false)
                            {
                                return -1;
                            }
                        }
                    }
                }
            }
            // g_Character_3.HandleInputAction_1(g_Event,g_Screen);
        }
        
        
        SDL_RenderClear(g_Screen);
        // Single_Player();
        game_status_machine();

        if(State == SINGPLEPLAYER_MODE) Single_Player();
        if(State == MULTIPLAYER_MODE) Multi_Player();
        if(State == QUIT_MODE) isquit = true;
        // g_BackGround.Render(g_Screen,NULL);

        if(is_skill)
        {
            Time_Break_Skill.LoadImage(Time_Break_Skill.list1[count_skill].c_str(),g_Screen,900,700);
            Time_Break_Skill.Render(g_Screen,NULL);
            if(count_skill >= 50)
            {
                count_skill = 0;
            }
            count_skill++;
            if(SDL_GetTicks() - finish.start_tick - time_pass >= 2000)
            {
                is_skill = false;
                count_skill = 0;
                finish.unpause();
                finish.start_tick += 5000;
                Run_Skill();
            }
        }

        if(is_skill_1)
        {

            Magic_Skill.LoadImage(Magic_Skill.list2[count_skill].c_str(),g_Screen,900,700);

            Magic_Skill.Render(g_Screen,NULL);
            // std::cout<<"hihi"<<std::endl;
            if(count_skill >= 17)
            {
                count_skill = 0;
            }
            count_skill++;
            if(SDL_GetTicks() - finish.start_tick - time_pass >= 1000)
            {
                is_skill_1 = false;
                count_skill = 0;
                finish.unpause();

                Run_Skill_1();
            }
        }

        SDL_RenderPresent(g_Screen);
        if(flag == 1) 
        {
            currentGameStatus = MENU_MODE;
            previousGameStatus = START_MODE;
            if(g_Menu.LoadMenu() == false)
            {
                return -1;
            }
            finish_option = false;
            start_flag = false;
            flag = 0;
        }
        int real_time = fps.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND ;//ms
        
        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            if(delay_time >=0) SDL_Delay(delay_time);
        }
    }
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();
    Close();
    return 0;
   
}