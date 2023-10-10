#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "common.h"

class BaseObject
{
public: 
    BaseObject();
    ~BaseObject();
    void SetRect(const int&x,const int&y){rect_.x=x;rect_.y=y;};
    SDL_Rect GetRect() const {return rect_;};
    SDL_Texture* GetTexture() const {return p_object_;};

    virtual bool LoadImage(std::string path, SDL_Renderer* screen,int rewidth , int reheight);
    // virtual bool LoadText(std::string path, SDL_Renderer* screen ,int value);
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Render_Score(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Render_Goal(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    // void Render_GoalFrame(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void SetClip();
    void SetClip1();
    void SetClip2();
    void Free();


    SDL_Texture* p_object_;
    SDL_Rect rect_;
    std::string list[26];
    std::string list1[60];
    std::string list2[17];

};

// extern BaseObject g_BackGround;
extern BaseObject g_BackGround1;
extern BaseObject GameTitle;
extern BaseObject SinglePlayerMode;
extern BaseObject MultiPlayerMode;
extern BaseObject OptionsMode;
extern BaseObject CreditsMode;
extern BaseObject QuitMode;

#endif