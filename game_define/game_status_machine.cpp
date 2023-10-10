#include "game_status_machine.h"

// int previousGameStatus=START_MODE;
// int currentGameStatus=START_MODE;

void game_status_machine(){

    switch (currentGameStatus)
    {
        case START_MODE:
            
            currentGameStatus= MENU_MODE;
            break;
        case MENU_MODE:
            
            if (previousGameStatus!=currentGameStatus)
            {

                g_BackGround1.Free();
                g_BackGround1.LoadImage(MENU_BACKGROUND,g_Screen,900,700);
                previousGameStatus=currentGameStatus;
                State = MENU_MODE;
            }

            g_BackGround1.Render(g_Screen,NULL);
            g_Menu.ShowMenu();
            g_Menu.RunMenu();
            break;

        case SINGPLEPLAYER_MODE:
            g_Menu.HiddenMenu();
            if (previousGameStatus!=currentGameStatus)
            {
                g_BackGround1.Free();
                g_BackGround1.LoadImage(SINGLEPLAYER_FOOTBALL_TURF_BACKGROUND,g_Screen,0,0);
                previousGameStatus=currentGameStatus;
                State = SINGPLEPLAYER_MODE;
            }
            g_BackGround1.Render(g_Screen,NULL);
            break;
        case MULTIPLAYER_MODE:
            g_Menu.HiddenMenu();
            if (previousGameStatus!=currentGameStatus)
            {
                g_BackGround1.Free();
                g_BackGround1.LoadImage(SINGLEPLAYER_FOOTBALL_TURF_BACKGROUND,g_Screen,0,0);
                previousGameStatus=currentGameStatus;
                State = MULTIPLAYER_MODE;
            }
            g_BackGround1.Render(g_Screen,NULL);
            break;
        
        case OPTIONS_MODE:
            g_Menu.HiddenMenu();
            if (previousGameStatus!=currentGameStatus)
            {
                g_BackGround1.Free();
                g_BackGround1.LoadImage("assets/Options_mode/options.png",g_Screen,0,0);
                previousGameStatus=currentGameStatus;
                State = MULTIPLAYER_MODE;
            }
            g_BackGround1.Render(g_Screen,NULL);
            State = OPTIONS_MODE;
            break;

        case CREDITS_MODE:
            g_Menu.HiddenMenu();
            State = CREDITS_MODE;
            
            break;
        case QUIT_MODE:
            g_Menu.HiddenMenu();
            State = QUIT_MODE;
            
            isQuit=true;
            break;

        default:
            break;
    }
}