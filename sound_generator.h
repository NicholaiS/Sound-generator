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
    void setduration(double d);
private:
    short SineWave(double time, double freq1, double freq2, double amp);
    double duration=0.2;
    sf::Sound sound;
};

#endif // SOUND_GENERATOR_H
