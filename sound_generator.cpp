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

    for(double i = 0; i < 44100*duration; i++)
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

void SoundGenerator::PlaySequence(std::string q){
    for(std::string::size_type i = 0; i < q.size(); i++){
            if(q[i]=='0'){
                PlaySingle(1336,941);
            }
            else if(q[i]=='1'){
                PlaySingle(1477,852);
            }
        }

}
