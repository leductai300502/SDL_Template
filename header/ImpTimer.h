#ifndef IMP_TIMER_H_
#define IMP_TIMERT_H_

#include "common.h"

class ImpTimer
{
public:
  ImpTimer();
  ~ImpTimer();



    void start();
    void stop();
    void pause();
    void unpause();

    int get_ticks();

    bool started();
    bool paused();

    int start_tick;
    int pause_tick;

    bool is_paused;
    bool is_started;

};


#endif