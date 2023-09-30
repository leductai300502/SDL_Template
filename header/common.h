#ifndef COMMON_H_
#define COMMON_H_

#include <windows.h>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

static SDL_Window* g_Window = NULL;
static SDL_Renderer* g_Screen = NULL;
static SDL_Event g_Event ;

const int SCREEN_WIDTH = 595;
const int SCREEN_HEIGHT = 800;
const int SCREEN_BPP = 32;

const int FRAME_PER_SECOND  = 25;
 
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

extern int force;

extern bool shoot;


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