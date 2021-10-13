#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H
#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <math.h>
#include <unistd.h>

enum direction
{
    FORWARD, BACKWARDS, LEFT, RIGHT
};

class SoundGenerator
{
public:
    SoundGenerator();
    short SineWave(double time, double freq1, double freq2, double amp);
    void PlaySound(double f1, double f2, double amp);
    void Movement(direction d);
    void Run();
};


#endif // SOUND_GENERATOR_H
