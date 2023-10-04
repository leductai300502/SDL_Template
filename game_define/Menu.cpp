#include "Menu.h"

BaseObject GameTitle;
BaseObject SinglePlayerMode;
BaseObject MultiPlayerMode;
BaseObject OptionsMode;
BaseObject CreditsMode;
BaseObject QuitMode;

Menu::Menu(int marginLeft, int marginTop, int gap){
    this->marginLeft=marginLeft;
    this->marginTop=marginTop;
    this->gap=gap;
    GameTitle.SetRect(this->marginLeft,this->marginTop);
    SinglePlayerMode.SetRect(this->marginLeft,GameTitle.GetRect().y+GAME_NAME_HEIGHT+this->gap);
    MultiPlayerMode.SetRect(this->marginLeft,SinglePlayerMode.GetRect().y+SINGLEPLAYER_BTN_HEIGHT+this->gap);
    OptionsMode.SetRect(this->marginLeft,MultiPlayerMode.GetRect().y+MULTIPLAYER_BTN_HEIGHT+this->gap);
    CreditsMode.SetRect(this->marginLeft,OptionsMode.GetRect().y+OPTIONS_BTN_HEIGHT+this->gap);
    QuitMode.SetRect(this->marginLeft,CreditsMode.GetRect().y+CREDITS_BTN_HEIGHT+this->gap);

    // std::cout<< "SinglePlayerMode: " <<SinglePlayerMode.GetRect().x<<std::endl;
    // std::cout<< "SinglePlayerMode: " <<SinglePlayerMode.GetRect().y<<std::endl;

    // std::cout<< "SinglePlayerMode: " <<MultiPlayerMode.GetRect().x<<std::endl;
    // std::cout<< "SinglePlayerMode: " <<MultiPlayerMode.GetRect().y<<std::endl;

    // std::cout<< "SinglePlayerMode: " <<OptionsMode.GetRect().x<<std::endl;
    // std::cout<< "SinglePlayerMode: " <<OptionsMode.GetRect().y<<std::endl;

    // std::cout<< "SinglePlayerMode: " <<CreditsMode.GetRect().x<<std::endl;
    // std::cout<< "SinglePlayerMode: " <<CreditsMode.GetRect().y<<std::endl;
}

Menu::~Menu(){
    GameTitle.Free();
    SinglePlayerMode.Free();
    MultiPlayerMode.Free();
    OptionsMode.Free();
    CreditsMode.Free();
    QuitMode.Free();
}

bool Menu::LoadMenu(){
    bool isGameTitleSuccess = GameTitle.LoadImage(MENU_GAME_NAME,g_Screen);
    bool isSinglePlayerModeSuccess = SinglePlayerMode.LoadImage(MENU_SINGLEPLAYER_BTN,g_Screen);
    bool isMultiPlayerModeSuccess = MultiPlayerMode.LoadImage(MENU_MULTIPLAYER_BTN,g_Screen);
    bool isOptionsModeSuccess = OptionsMode.LoadImage(MENU_OPTIONS_BTN,g_Screen);
    bool isCreditsModeSuccess = CreditsMode.LoadImage(MENU_CREDITS_BTN,g_Screen);
    bool isQuitModeSuccess = QuitMode.LoadImage(MENU_QUIT_BTN,g_Screen);

    // checking error when loading image
    if(!isGameTitleSuccess ||
        !isSinglePlayerModeSuccess ||
        !isMultiPlayerModeSuccess ||
        !isOptionsModeSuccess ||
        !isCreditsModeSuccess ||
        !isQuitModeSuccess)
    {
        if(!isGameTitleSuccess){
            std::cout<< "Loading Game Title Image failed!"<<std::endl;
        } 
        if(!isSinglePlayerModeSuccess){
            std::cout<< "Loading Single Player Button Image failed!"<<std::endl;
        }     
        if(!isMultiPlayerModeSuccess){
            std::cout<< "Loading Mutilple Player Button Image failed!"<<std::endl;
        }     
        if(!isOptionsModeSuccess){
            std::cout<< "Loading Options Button Image failed!"<<std::endl;
        }     
        if(!isCreditsModeSuccess){
            std::cout<< "Loading Credits Button Image failed!"<<std::endl;
        }     
        if(!isQuitModeSuccess){
            std::cout<< "Loading Quit Button Image failed!"<<std::endl;
        }         

        return false;

    }
    // std::cout<< "Loading Menu successfully"<<std::endl;
    
    return true;
}

void Menu::ShowMenu(){
    // std::cout<<"Menu is rendering"<<std::endl;
    GameTitle.Render(g_Screen,NULL);
    SinglePlayerMode.Render(g_Screen,NULL);
    MultiPlayerMode.Render(g_Screen,NULL);
    OptionsMode.Render(g_Screen,NULL);
    CreditsMode.Render(g_Screen,NULL);
    QuitMode.Render(g_Screen,NULL);
}

void Menu::HiddenMenu(){
    GameTitle.Free();
    SinglePlayerMode.Free();
    MultiPlayerMode.Free();
    OptionsMode.Free();
    CreditsMode.Free();
    QuitMode.Free();
}

void Menu::RunMenu(){
    if(g_Event.button.button==SDL_BUTTON_LEFT){
        if(g_Event.button.type == SDL_MOUSEBUTTONUP){
            //clicking SINGLEPLAYER mode
            if(g_Event.button.x > this->marginLeft && g_Event.button.x <(this->marginLeft+SINGLEPLAYER_BTN_WIDTH)){
                int marginTopOfButton=GameTitle.GetRect().y+GAME_NAME_HEIGHT+this->gap;
                if(g_Event.button.y >marginTopOfButton && g_Event.button.y<(marginTopOfButton+SINGLEPLAYER_BTN_HEIGHT)){
                    currentGameStatus = SINGPLEPLAYER_MODE;
                    std::cout<< "Changing to SINGPLEPLAYER_MODE"<<std::endl;
                }
            }

            //clicking MULTIPLAYER mode
            if(g_Event.button.x > this->marginLeft && g_Event.button.x <(this->marginLeft+MULTIPLAYER_BTN_WIDTH)){
                int marginTopOfButton=SinglePlayerMode.GetRect().y+SINGLEPLAYER_BTN_HEIGHT+this->gap;
                if(g_Event.button.y >marginTopOfButton && g_Event.button.y<(marginTopOfButton+MULTIPLAYER_BTN_HEIGHT)){
                    currentGameStatus = MULTIPLAYER_MODE;
                    std::cout<< "Changing to MULTIPLAYER_MODE"<<std::endl;

                }
            }

            //clicking OPTIONS mode
            if(g_Event.button.x > this->marginLeft && g_Event.button.x <(this->marginLeft+OPTIONS_BTN_WIDTH)){
                int marginTopOfButton=MultiPlayerMode.GetRect().y+MULTIPLAYER_BTN_HEIGHT+this->gap;
                if(g_Event.button.y >marginTopOfButton && g_Event.button.y<(marginTopOfButton+OPTIONS_BTN_HEIGHT)){
                    currentGameStatus = OPTIONS_MODE;
                    std::cout<< "Changing to OPTIONS_MODE"<<std::endl;

                }
            }

            //clicking CREDITS mode
            if(g_Event.button.x > this->marginLeft && g_Event.button.x <(this->marginLeft+CREDITS_BTN_WIDTH)){
                int marginTopOfButton=OptionsMode.GetRect().y+OPTIONS_BTN_HEIGHT+this->gap;
                if(g_Event.button.y >marginTopOfButton && g_Event.button.y<(marginTopOfButton+CREDITS_BTN_HEIGHT)){
                    currentGameStatus = CREDITS_MODE;
                    std::cout<< "Changing to CREDITS_MODE"<<std::endl;

                }
            }

            //clicking QUIT mode
            if(g_Event.button.x > this->marginLeft && g_Event.button.x <(this->marginLeft+QUIT_BTN_WIDTH)){
                int marginTopOfButton=CreditsMode.GetRect().y+CREDITS_BTN_HEIGHT+this->gap;
                if(g_Event.button.y >marginTopOfButton && g_Event.button.y<(marginTopOfButton+QUIT_BTN_HEIGHT)){
                    currentGameStatus = QUIT_MODE;
                    std::cout<< "Changing to QUIT_MODE"<<std::endl;

                }
            }
        }
    }
}
