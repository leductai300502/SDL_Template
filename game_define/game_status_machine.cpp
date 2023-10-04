#include "game_status_machine.h"

int previousGameStatus=START_MODE;
int currentGameStatus=START_MODE;

void game_status_machine(){

    switch (currentGameStatus)
    {
        case START_MODE:
            
            currentGameStatus= MENU_MODE;
            break;
        case MENU_MODE:
            
            if (previousGameStatus!=currentGameStatus)
            {
                
                g_BackGround.Free();
                g_BackGround.LoadImage(MENU_BACKGROUND,g_Screen);
                previousGameStatus=currentGameStatus;
            }
            
            // g_Menu.ShowMenu();
            g_Menu.RunMenu();
            break;

        case SINGPLEPLAYER_MODE:
            g_Menu.HiddenMenu();
            if (previousGameStatus!=currentGameStatus)
            {
                g_BackGround.Free();
                g_BackGround.LoadImage(SINGLEPLAYER_FOOTBALL_TURF_BACKGROUND,g_Screen);
                previousGameStatus=currentGameStatus;
            }
            break;
        case MULTIPLAYER_MODE:
            g_Menu.HiddenMenu();
            if (previousGameStatus!=currentGameStatus)
            {
                g_BackGround.Free();
                g_BackGround.LoadImage(SINGLEPLAYER_FOOTBALL_TURF_BACKGROUND,g_Screen);
                previousGameStatus=currentGameStatus;
            }
            
            break;
        
        case OPTIONS_MODE:
            g_Menu.HiddenMenu();
            
            break;

        case CREDITS_MODE:
            g_Menu.HiddenMenu();

            
            break;
        case QUIT_MODE:
            g_Menu.HiddenMenu();

            
            isQuit=true;
            break;

        default:
            break;
    }
}