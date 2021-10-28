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
    void Movement(direction d);
    void PlaySingle(double f1, double f2);
    void Run();
private:
    void PlayLoop(double f1, double f2);
    short SineWave(double time, double freq1, double freq2, double amp);
    sf::Sound lsound;
    sf::SoundBuffer lbuffer;
};

#endif // SOUND_GENERATOR_H
