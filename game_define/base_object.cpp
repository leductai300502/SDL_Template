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

bool BaseObject::LoadImage(std::string path, SDL_Renderer* screen , int rewidth, int reheight)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadSurface = IMG_Load(path.c_str());

    if(loadSurface != NULL)
    {
        // SDL_SetColorKey(loadSurface,SDL_TRUE,SDL_MapRGB(loadSurface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen,loadSurface);
        if(newTexture != NULL)
        {
            if(rewidth != 0 && reheight != 0 )
            {
                rect_.h = reheight;
                rect_.w = rewidth;
            }
            else{
                rect_.h = loadSurface ->h;
                rect_.w = loadSurface ->w;
            }
        }
        SDL_FreeSurface(loadSurface);
    }

    p_object_ = newTexture;
    return p_object_ ;
}



void BaseObject::Render(SDL_Renderer* des,const SDL_Rect* clip)
{
    SDL_Rect renderquad = {rect_.x,rect_.y,rect_.w,rect_.h};

    SDL_RenderCopy(des,p_object_,clip, &renderquad);
}

void BaseObject::Render_Goal(SDL_Renderer* des,const SDL_Rect* clip)
{
    SDL_Rect renderquad = {-10,30,rect_.w,rect_.h};

    SDL_RenderCopy(des,p_object_,clip, &renderquad);
}
// void BaseObject::Render_GoalFrame(SDL_Renderer* des,const SDL_Rect* clip)
// {
//     SDL_Rect renderquad = {70,110,rect_.w,rect_.h};

//     SDL_RenderCopy(des,p_object_,clip, &renderquad);
// }

void BaseObject::Render_Score(SDL_Renderer* des,const SDL_Rect* clip)
{
    SDL_Rect renderquad = {100,10,rect_.w,rect_.h};

    SDL_RenderCopy(des,p_object_,clip, &renderquad);
}

void BaseObject::SetClip()
{
    list[0] = "celebrate/ga.gif";
    list[1] = "celebrate/gb.gif";
    list[2] = "celebrate/gc.gif";
    list[3] = "celebrate/gd.gif";
    list[4] = "celebrate/ge.gif";
    list[5] = "celebrate/gf.gif";
    list[6] = "celebrate/gg.gif";
    list[7] = "celebrate/gh.gif";
    list[8] = "celebrate/gi.gif";
    list[9] = "celebrate/gj.gif";
    list[10] = "celebrate/gk.gif";
    list[11] = "celebrate/gl.gif";
    list[12] = "celebrate/gm.gif";
    list[13] = "celebrate/gn.gif";
    list[14] = "celebrate/go.gif";
    list[15] = "celebrate/gp.gif";
    list[16] = "celebrate/gq.gif";
    list[17] = "celebrate/gr.gif";
    list[18] = "celebrate/gs.gif";
    list[19] = "celebrate/gt.gif";
    list[20] = "celebrate/gu.gif";
    list[21] = "celebrate/gv.gif";
    list[22] = "celebrate/gw.gif";
    list[23] = "celebrate/gx.gif";
    list[24] = "celebrate/gy.gif";
    list[25] = "celebrate/gz.gif";
    // list[26] = "celebrate/ga.gif";
}

void BaseObject::SetClip1()
{
    for(int i =0 ; i<60;i++)
    {
        list1[i] = "assets/Ekko/11zon_"+ std::to_string(i+1) +".jpeg";
    }
}

void BaseObject::SetClip2()
{
    for(int i =0 ; i<17;i++)
    {
        list2[i] = "assets/itachi/5a183430be1e48d5cfa56c595d82e806180pyf0CrxK8GK4D-"+ std::to_string(i) +".jpg";
    }
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