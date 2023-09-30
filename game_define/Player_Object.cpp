#include "Player_Object.h"

PlayerObject::PlayerObject()
{
    // is_falling_ = false;
    x_val_ = 0;
    y_val_ = 0;
    width_frame =0;
    height_frame =0;
    frame =0;
    status =1;
    x_pos_ =0;
    y_pos_ =0;
    input_type.up=0;
    input_type.left=0;
    input_type.right=0;
    input_type.down=0;
    input_type.up_left=0;
    input_type.up_right=0;
    input_type.down_left=0;
    input_type.down_right=0;
}

PlayerObject::~PlayerObject()
{
    BaseObject::Free();
}

bool PlayerObject::LoadImg(std::string path, SDL_Renderer* screen)
{
  bool ret = BaseObject::LoadImage(path, screen);
  if(ret)
  {
    width_frame  = rect_.w/8;
    height_frame = rect_.h;
  }
  return ret;
}

void PlayerObject::Center()
{
  x_center = x_pos_+ (width_frame/2);
  y_center = y_pos_ + (height_frame/2);

  // std::cout << x_center<<";"<<y_center<<std::endl;
}

void PlayerObject::Show(SDL_Renderer* des)
{
  //  BaseObject::Render(des,NULL);
  if(status == Walk_left )
  {
    LoadImg("player_left.png",des);
  }
  else if(status == Walk_rigth)
  {
    LoadImg("player_right.png",des);
  }
  else if(status == Walk_down)
  {
    LoadImg("player_left.png",des);
  }
  else{
    LoadImg("player_right.png",des);
  }
  
  // if(input_type.left == 1 && input_type.up == 1)
  // {
  //   frame ++;
  //   if(x_pos_ >= 5 )
  //   {
  //     x_pos_ -= 5;
  //   } 
  //   if(y_pos_ >= 5)
  //   {
  //     y_pos_ -= 5;
  //   }
  //   input_type.left = 0;
  //   input_type.up = 0;
  // }
  // else if(input_type.up == 1 && input_type.right == 1)
  // {
  //   frame++;
  //   if(x_pos_ + width_frame <= SCREEN_WIDTH -5){
  //     x_pos_ += 5;
  //   }
  //   if(y_pos_ >= 5)
  //   {
  //     y_pos_ -= 5;
  //   }
  //   input_type.right = 0;
  //   input_type.up = 0;
  // }
  // else if(input_type.down == 1 && input_type.right == 1)
  // {
  //   frame++;
  //   if(x_pos_ + width_frame <= SCREEN_WIDTH -5 ){
  //     x_pos_ += 5;
  //   }
  //   if(y_pos_ + height_frame <= SCREEN_HEIGHT -5)
  //   {
  //     y_pos_ += 5;
  //   }
  //   input_type.right = 0;
  //   input_type.down = 0;
  // }
  // else if(input_type.down == 1 && input_type.left == 1)
  // {
  //   frame++;
  //   if(x_pos_ >= 5 ){
  //     x_pos_ -= 5;
  //   }
  //   if(y_pos_ + height_frame <= SCREEN_HEIGHT -5)
  //   {
  //      y_pos_ += 5;
  //   }
  //   input_type.left = 0;
  //   input_type.up = 0;
  // }
  // else if(input_type.left == 1)
  // {
  //   frame++;
  //   if(x_pos_ >= 5) x_pos_ -=5;
  //   input_type.left = 0;
  //   // std::cout<<x_pos_<<std::endl;
  // }
  // else if(input_type.right == 1)
  // {
  //   frame++;
  //   if(x_pos_ <= SCREEN_WIDTH - width_frame - 5) x_pos_ +=5;
  //   input_type.right = 0;
  // }
  // else if(input_type.up == 1)
  // {
  //   frame++;
  //   if(y_pos_ >= 5) y_pos_ -= 5;
  //   input_type.up = 0;
  // }
  // else if(input_type.down == 1)
  // {
  //   frame++;
  //   if(y_pos_ + height_frame <= SCREEN_HEIGHT - 5) y_pos_ += 5;
  //   input_type.down = 0;
  // }
  // else{
  //   frame =0;
  // }

  if(input_type.left == 1)
  {
    frame ++;
    if(x_pos_ >= 5 )
    {
      x_pos_ -= 5;
    } 
  }
  if(input_type.right == 1)
  {
    frame++;
    if(x_pos_ + width_frame <= SCREEN_WIDTH -5){
      x_pos_ += 5;
    }
  }
  if(input_type.up == 1)
  {
    frame++;
    if(y_pos_ >= 5)
    {
      y_pos_ -= 5;
    }
  }
  if(input_type.down == 1)
  {
    frame++;
    if(y_pos_ + height_frame <= SCREEN_HEIGHT -5)
    {
      y_pos_ += 5;
    }
  }
  if(input_type.left == 0 && input_type.right == 0 && input_type.down == 0 && input_type.up == 0)
  {
    frame = 0;
  }
  if(frame >= 8)
  {
    frame = 0;
  }

  rect_.x = x_pos_;
  rect_.y = y_pos_;

  SDL_Rect* current_clip = &frame_clip[frame];
  SDL_Rect renderQuad = {rect_.x,rect_.y,width_frame,height_frame};
  SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
}

void PlayerObject::HandleInputAction_1(SDL_Event events, SDL_Renderer* screen)
{
  if(events.type == SDL_KEYDOWN)
  {
    if(events.key.keysym.sym == SDLK_LEFT)
    {
      status = Walk_left;
      input_type.left = 1;
    }
    if(events.key.keysym.sym == SDLK_RIGHT)
    {
      status = Walk_rigth;
      input_type.right = 1;
    }
    if(events.key.keysym.sym == SDLK_UP)
    {
      status = Walk_up;
      input_type.up = 1;
    }    
    if(events.key.keysym.sym == SDLK_DOWN)
    {
      status = Walk_down;
      input_type.down = 1;
    }   
  }else if(events.type == SDL_KEYUP)
  {
    switch (events.key.keysym.sym)
    {
      case SDLK_RIGHT:
        {
          // status = Walk_rigth;
          input_type.right = 0;
        }
        break;
      case SDLK_LEFT:
        {
          // status = Walk_left;
          input_type.left = 0;
        }
      case SDLK_UP:
        {
          // status = Walk_rigth;
          input_type.up = 0;
        }
        break;
      case SDLK_DOWN:
        {
          // status = Walk_left;
          input_type.down = 0;
        }        
        break;
    }
  }
}

void PlayerObject::HandleInputAction_2(SDL_Event events, SDL_Renderer* screen)
{
  if(events.type == SDL_KEYDOWN)
  {
    if(events.key.keysym.sym == SDLK_a)
    {
      status = Walk_left;
      input_type.left = 1;
    }
    if(events.key.keysym.sym == SDLK_d)
    {
      status = Walk_rigth;
      input_type.right = 1;
    }
    if(events.key.keysym.sym == SDLK_w)
    {
      status = Walk_up;
      input_type.up = 1;
    }    
    if(events.key.keysym.sym == SDLK_s)
    {
      status = Walk_down;
      input_type.down = 1;
    }   
  }else if(events.type == SDL_KEYUP)
  {
    switch (events.key.keysym.sym)
    {
      case SDLK_d:
        {
          // status = Walk_rigth;
          input_type.right = 0;
        }
        break;
      case SDLK_a:
        {
          // status = Walk_left;
          input_type.left = 0;
        }
      case SDLK_w:
        {
          // status = Walk_rigth;
          input_type.up = 0;
        }
        break;
      case SDLK_s:
        {
          // status = Walk_left;
          input_type.down = 0;
        }        
        break;
    }
  }
}


void PlayerObject::Set_Clip()
{
  if(width_frame > 0 and height_frame >= 0)
  {
    for(int i =0 ; i< 8 ;i++)
    {
      frame_clip[i].x = i*width_frame;
      frame_clip[i].y = 0;
      frame_clip[i].w = width_frame;
      frame_clip[i].h = height_frame;
    }
  }
}

// void PlayerObject::DoFalling(SDL_Renderer* des)
// {
//     rect_.y += y_val_;
//     if ((rect_.y + rect_.h) >= GROUND_MAP)
//     {
//         LoadImg("img//fl_bird2.png", des);
//         is_falling_ = true;
//         DoGround(des);
//     }
// }

// void PlayerObject::DoGround(SDL_Renderer* screen)
// {
//     y_val_ = 0;
//     rect_.y = GROUND_MAP - rect_.h;
//     is_die_ = true;
// }