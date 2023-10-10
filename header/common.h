#ifndef COMMON_H_
#define COMMON_H_

#include <windows.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "base_object.h"
#include "Menu.h"

static SDL_Window* g_Window = NULL;
// static SDL_Renderer* g_Screen = NULL;
// static SDL_Event g_Event ;
extern SDL_Renderer* g_Screen;
extern SDL_Event g_Event ;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

const int SCREEN_WIDTH_YARD_S = 75;
const int SCREEN_WIDTH_YARD_M = 825;
const int SCREEN_HEIGHT_YARD_S = 100;
const int SCREEN_HEIGHT_YARD_M = 600;
const int SCREEN_BPP = 32;

const int FRAME_PER_SECOND  = 25;
 
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

extern int force;

extern bool shoot;
extern bool isQuit;

extern int State;

extern int previousGameStatus;
extern int currentGameStatus; /// store current status

// extern BaseObject g_BackGround;


typedef struct
{
    int left;
    int right;
    int up;
    int down;
    int up_right;
    int up_left;
    int down_right;
    int down_left;
}Input;


#endif