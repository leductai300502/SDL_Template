#ifndef MENU_H
#define MENU_H

#include "base_object.h"
#include "common.h"
#include "img_link.h"
#include "game_status_machine.h"


#define GAME_NAME_WIDTH 399
#define GAME_NAME_HEIGHT 65

#define SINGLEPLAYER_BTN_WIDTH 319
#define SINGLEPLAYER_BTN_HEIGHT 69

#define MULTIPLAYER_BTN_WIDTH 319
#define MULTIPLAYER_BTN_HEIGHT 69

#define OPTIONS_BTN_WIDTH 319
#define OPTIONS_BTN_HEIGHT 69

#define CREDITS_BTN_WIDTH 319
#define CREDITS_BTN_HEIGHT 69

#define QUIT_BTN_WIDTH 319
#define QUIT_BTN_HEIGHT 69


class Menu
{
private:
    /* data */
    // BaseObject GameTitle;
    // BaseObject SinglePlayerMode;
    // BaseObject MultiPlayerMode;
    // BaseObject OptionsMode;
    // BaseObject CreditsMode;
    // BaseObject QuitMode;

    int marginLeft;
    int marginTop;
    int gap;
public:
    Menu(int marginLeft=500, int marginTop=50, int gap=31);
    ~Menu();
    bool LoadMenu();
    void ShowMenu();
    void HiddenMenu();
    void RunMenu();
};

extern Menu g_Menu;


#endif