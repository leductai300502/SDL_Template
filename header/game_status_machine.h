#ifndef GAME_STATUS_MACHINE_H_
#define GAME_STATUS_MACHINE_H_

#include "common.h"
#include "img_link.h"

//// Control all status changing in game ////

#define START_MODE 10000
#define MENU_MODE 10001
#define SINGPLEPLAYER_MODE 10002
#define MULTIPLAYER_MODE 10003
#define OPTIONS_MODE 10004
#define CREDITS_MODE 10005
#define QUIT_MODE 10006

extern int gameStatus; /// store current status

void game_status_machine(); /// changing status

#endif