#ifndef BALL_OBJECT_H_
#define BALL_OBJECT_H_

#include "common.h"
#include "base_object.h"

class BallObject : public BaseObject
{
public:
  BallObject();
  ~BallObject();


  bool LoadImg(std::string path, SDL_Renderer* screen);
  void Show(SDL_Renderer* des);
  void HandleMoveAction(SDL_Event events, SDL_Renderer* screen); 
  void Center();

  float x_val_;
  float y_val_;

  float Force;
  float angle;

  float x_pos_;
  float y_pos_;

  float x_center;
  float y_center;

  int width_frame;
  int height_frame;

  int corner;


  int frame;
  int status;

  bool is_move_;
  bool is_prevent_;
  bool is_goal;

  Input input_type;

};


#endif