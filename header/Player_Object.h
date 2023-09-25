#ifndef PLAYER_OBJECT_H_
#define PLAYER_OBJECT_H_

#include "common.h"
#include "base_object.h"

class PlayerObject : public BaseObject
{
public:
  PlayerObject();
  ~PlayerObject();


  int  Walk_rigth = 0;
  int  Walk_left = 1;
  int  Walk_up = 2;
  int  Walk_down = 3;
  int  Walk_up_right = 4;
  int  Walk_up_left =  5;
  int  Walk_down_right = 6;
  int  Walk_down_left = 7;

  bool LoadImg(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* des);
  void HandleInputAction(SDL_Event events, SDL_Renderer* screen); 
  void Set_Clip();
  void Center();

  float x_val_;
  float y_val_;

  float x_center;
  float y_center;

  float x_pos_;
  float y_pos_;

  int width_frame;
  int height_frame;

  SDL_Rect frame_clip[8];
  int frame;
  int status;

  bool is_shoot_;
  bool is_prevent_;
  bool is_goal;

  Input input_type;
};


#endif