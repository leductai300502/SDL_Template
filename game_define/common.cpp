#include "common.h"

SDL_Renderer* g_Screen=NULL;
BaseObject g_BackGround;
SDL_Event g_Event ;

Menu g_Menu;

bool isQuit=false;
int force = 100;

bool shoot = false;