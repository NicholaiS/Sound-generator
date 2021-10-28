#include "sound_generator.h"
#include "SFML/Audio.hpp"
#include <math.h>


SoundGenerator::SoundGenerator()
{

}



short SoundGenerator::SineWave(double time, double freq1, double freq2, double amp)
{
    #define TWO_PI 6.28318530718

    short result;
    double tpc1 = 44100/freq1;
    double cycle1 = time / tpc1;
    double rad1 = TWO_PI * cycle1;
    short A1 = 32767 * amp;

    double tpc2 = 44100/freq2;
    double cycle2 = time / tpc2;
    double rad2 = TWO_PI * cycle2;
    short A2 = 32767 * amp;

    result = A1 * sin(rad1) + A2 * sin(rad2);

    return result;
}


void SoundGenerator::PlaySingle(double f1, double f2){
    sf::Sound ssound;
    sf::SoundBuffer sbuffer;
    std::vector<sf::Int16> ssamples;

    for(double i = 0; i < 44100; i++)
    {
        ssamples.push_back(SineWave(i, f1, f2, 0.1));
    }

    sbuffer.loadFromSamples(&ssamples[0], ssamples.size(), 1, 44100);

    ssound.setBuffer(sbuffer);
    ssound.play();
    while(ssound.getStatus()==2){};
}

void SoundGenerator::PlayLoop(double f1, double f2)
{
    if(lsound.getStatus()!=2){
    std::vector<sf::Int16> samples;

    for(double i = 0; i < 44100; i++)
    {
        samples.push_back(SineWave(i, f1, f2, 0.1));
    }

    lbuffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);

    lsound.setBuffer(lbuffer);
    lsound.setLoop(true);
    lsound.play();
    }

}

void SoundGenerator::Movement(direction d)
{
    switch(d)
    {
        case FORWARD:
        PlayLoop(1336, 697);
        break;

        case BACKWARDS:
        PlayLoop(1336, 852);
        break;

        case LEFT:
        PlayLoop(1209, 770);
        break;

        case RIGHT:
        PlayLoop(1477, 770);
    }
}

void SoundGenerator::Run()
{
    initscr();
    printw("tryk for at starte");
    getch();
    timeout(100);
    int input;
    do
    {
        input = getch();
        clear();

        if(input == 'w')  {
            Movement(FORWARD);
        }
        else if(input=='s') {
            Movement(BACKWARDS);
        } else if(input=='a'){
            Movement(LEFT);
        } else if(input=='d'){
            Movement(RIGHT);
        } else {
            lsound.stop();
        };
    } while (input != 'e');
}
