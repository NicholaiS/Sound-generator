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

    double j = 44100*duration;

    for(double i = 0; i < j; i++)
    {
        ssamples.push_back(SineWave(i, f1, f2, 0.1));
    }

    for(double i = 0; i < j; i++)
    {
        ssamples[i]=ssamples[i]*(0.54+0.46*cos((i*M_PI)/j));
    }

    sbuffer.loadFromSamples(&ssamples[0], ssamples.size(), 1, 44100);

    ssound.setBuffer(sbuffer);
    ssound.play();
    while(ssound.getStatus()==2){};
}

void SoundGenerator::setduration(double d){
    duration=d;
}

void SoundGenerator::PlaySequence(std::string q){
    usleep(862500);
    for(std::string::size_type i = 0; i < q.size(); i++){
            if(q[i]=='0'){
                PlaySingle(941,1633);
            }
            else if(q[i]=='1'){
                PlaySingle(852,1477);
            }
        }

}
