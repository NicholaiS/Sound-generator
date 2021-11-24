#ifndef SOUND_GENERATOR_H
#define SOUND_GENERATOR_H
#include <iostream>
#include "SFML/Audio.hpp"
#include <vector>
#include <math.h>
#include <unistd.h>

class SoundGenerator
{
public:
    SoundGenerator();
    void PlaySingle(double f1, double f2);
    void PlaySequence(std::string q);
    void PlayLoop(double f1, double f2);
    sf::Sound lsound;
    void setduration(double d);
private:
    short SineWave(double time, double freq1, double freq2, double amp);
    sf::SoundBuffer lbuffer;
    double duration=0.2;
};

#endif // SOUND_GENERATOR_H
