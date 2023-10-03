#include "game_status_machine.h"

int gameStatus=START_MODE;

void game_status_machine(){

    switch (gameStatus)
    {
        case START_MODE:
            /* code */
            gameStatus= MENU_MODE;
            break;
        case MENU_MODE:
            /* code */
            g_BackGround.LoadImage(MENU_BACKGROUND,g_Screen);
            g_Menu.ShowMenu();
            g_Menu.RunMenu();
            break;

        case SINGPLEPLAYER_MODE:
            g_Menu.HiddenMenu();
            g_BackGround.LoadImage(SINGLEPLAYER_FOOTBALL_TURF_BACKGROUND,g_Screen);
            /* code */
            break;
        case MULTIPLAYER_MODE:
            g_Menu.HiddenMenu();
            g_BackGround.LoadImage(SINGLEPLAYER_FOOTBALL_TURF_BACKGROUND,g_Screen);
            /* code */
            break;
        
        case OPTIONS_MODE:
            g_Menu.HiddenMenu();
            /* code */
            break;

        case CREDITS_MODE:
            g_Menu.HiddenMenu();

            /* code */
            break;
        case QUIT_MODE:
            g_Menu.HiddenMenu();

            /* code */
            isQuit=true;
            break;

        default:
            break;
    }
}