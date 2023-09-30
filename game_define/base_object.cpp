#include "base_object.h"


BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.h =0;
    rect_.w =0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImage(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadSurface = IMG_Load(path.c_str());

    if(loadSurface != NULL)
    {
        SDL_SetColorKey(loadSurface,SDL_TRUE,SDL_MapRGB(loadSurface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen,loadSurface);
        if(newTexture != NULL)
        {
            rect_.h = loadSurface ->h;
            rect_.w = loadSurface ->w;
        }
        SDL_FreeSurface(loadSurface);
    }

    p_object_ = newTexture;
    return p_object_ ;
}

bool BaseObject::LoadText(std::string path, SDL_Renderer* screen , int value )
{
    SDL_Texture* newTexture = NULL;
    TTF_Font* font = TTF_OpenFont(path.c_str(), 24);

    std::string text = std::to_string(value);
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255}); // Text, color

    if(textSurface != NULL)
    {
        newTexture = SDL_CreateTextureFromSurface(screen,textSurface);
        if(newTexture != NULL)
        {
            rect_.h = textSurface ->h;
            rect_.w = textSurface ->w;
        }
        SDL_FreeSurface(textSurface);
    }

    newTexture = SDL_CreateTextureFromSurface(screen, textSurface);
    return newTexture ;
}

void BaseObject::Render(SDL_Renderer* des,const SDL_Rect* clip)
{
    SDL_Rect renderquad = {rect_.x,rect_.y,rect_.w,rect_.h};

    SDL_RenderCopy(des,p_object_,clip, &renderquad);
}

void BaseObject::Free()
{
    if(p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h =0;
    }
}