#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
    start_tick = 0;
    pause_tick = 0;
    is_paused = false;
    is_started = false;
}

ImpTimer::~ImpTimer()
{
    
}

void ImpTimer::start()
{
    is_started = true;
    is_paused = false;
    start_tick = SDL_GetTicks();
}

void ImpTimer::stop()
{
    is_started = false;
    is_paused = false;
    // start_tick = SDL_GetTicks();
}

void ImpTimer::pause()
{
    if(is_started == true && is_paused == false) is_paused = true;
    pause_tick = SDL_GetTicks() - start_tick;
}

void ImpTimer::unpause()
{
    if(is_paused == true) is_paused = false;
    start_tick = SDL_GetTicks() - pause_tick;
    pause_tick = 0;
}

int ImpTimer::get_ticks()
{
    if(is_started == true )
    {
        if(is_paused == true)
        {
            return pause_tick;
        }
        else{
            return SDL_GetTicks() - start_tick; 
        }
    }
    return 0;
}

bool ImpTimer::started()
{
    return is_started;
}

bool ImpTimer::paused()
{
    return is_paused;
}