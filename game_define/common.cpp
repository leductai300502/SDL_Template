#include "common.h"


// BaseObject background;

SDL_Renderer* g_Screen=NULL;
// BaseObject g_BackGround;
SDL_Event g_Event ;

BaseObject g_BackGround1;
Menu g_Menu;

int force = 100;

int State = START_MODE;

int previousGameStatus=START_MODE;
int currentGameStatus=START_MODE;

bool shoot = false;
bool isQuit=false;