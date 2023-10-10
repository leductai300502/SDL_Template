#include "Ball_Object.h"

BallObject::BallObject()
{
    x_val_ = 0;
    y_val_ = 0;
    width_frame =0;
    height_frame =0;
    frame =0;
    status =0;
    x_pos_ =100;
    y_pos_ =0;
    Force = 0;
    angle = 0;
    is_move_ = false;
    corner = 0;
    
    input_type.left = 0;
    input_type.right = 0;
    input_type.up = 0;
    input_type.down = 0;
}

BallObject::~BallObject()
{
    BaseObject::Free();
}

bool BallObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImage(path, screen,0,0);
  if(ret)
  {
    width_frame  = rect_.w;
    height_frame = rect_.h;
  }
  return ret;
}

void BallObject::Center()
{
  x_center = x_pos_+ (width_frame/2);
  y_center = y_pos_ + (height_frame/2);
//   std::cout<<width_frame<<":::::"<<height_frame<<std::endl;
//   std::cout<<x_pos_<<" ---"<<y_pos_<<std::endl;
//   std::cout << x_center<<";"<<y_center<<std::endl;
}

void BallObject::Show(SDL_Renderer* des)
{

  LoadImg("ball.png",des);


  rect_.x = x_pos_;
  rect_.y = y_pos_;

  SDL_Rect renderQuad = {rect_.x,rect_.y,width_frame,height_frame};
  SDL_RenderCopy(des,p_object_,NULL,&renderQuad);
}

void BallObject::HandleMoveAction(SDL_Event events, SDL_Renderer* screen)
{
  
}

