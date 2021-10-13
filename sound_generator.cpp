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

void SoundGenerator::PlaySound(double f1, double f2, double amp)
{
    sf::RenderWindow window(sf::VideoMode(800,600),"My window");

    //Kode skriver her:
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;

    for(double i = 0; i < 44100; i++)
    {
        samples.push_back(SineWave(i, f1, f2, amp));
    }

    buffer.loadFromSamples(&samples[0], samples.size(), 1, 44100);

    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    //Kode stopper her.

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}

void SoundGenerator::Movement(direction d)
{
    switch(d)
    {
        case FORWARD:
        PlaySound(1336, 697, 0.1);
        break;

        case BACKWARDS:
        PlaySound(1336, 852, 0.1);
        break;

        case LEFT:
        PlaySound(1209, 770, 0.1);
        break;

        case RIGHT:
        PlaySound(1477, 770, 0.1);
        break;
    }
}

void SoundGenerator::Run()
{
    char input;
    do
    {
        std::cin >> input;

        switch(input)
        {
        case '0':
            system("clear");
            std::cout << "Program ended." << std::endl;
            break;

        case 'w':
            Movement(FORWARD);
            break;

        case 's':
            Movement(BACKWARDS);
            break;

        case 'a':
            Movement(LEFT);
            break;

        case 'd':
            Movement(RIGHT);
            break;
        }
    }
    while (input != '0');
}
