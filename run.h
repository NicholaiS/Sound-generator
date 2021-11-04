#ifndef RUN_H
#define RUN_H
#include "sound_generator.h"
#include <ncurses.h>

enum direction
{
    FORWARD, BACKWARDS, LEFT, RIGHT
};

class Run : SoundGenerator
{
public:
    Run();
    void run();
private:
    void Movement(direction d);
};

#endif // RUN_H
