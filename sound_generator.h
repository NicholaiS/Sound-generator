#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H
#include <iostream>
#include "SFML/Audio.hpp"
#include <vector>
#include <math.h>
#include <unistd.h>
#include <ncurses.h>

enum direction
{
    FORWARD, BACKWARDS, LEFT, RIGHT
};

class SoundGenerator
{
public:
    SoundGenerator();
    void SetDuration(double s);
    void Movement(direction d);
    void Run();
private:
    void PlaySound(double f1, double f2, double amp);
    short SineWave(double time, double freq1, double freq2, double amp);
    double _duration = 1; //må ikke komme under 0.3
};

#endif // SOUND_GENERATOR_H
