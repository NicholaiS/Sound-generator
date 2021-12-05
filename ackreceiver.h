#ifndef ACK_RECEIVER_H
#define ACK_RECEIVER_H

#include <iostream>
#include <cmath>
#include <unistd.h>
#include <string>
#include "SFML/Audio.hpp"


class Response
{
public:
    Response();
    int ResponseRecognition();
    void FindMic();
private:
    double GoertzelAlgorithm(int SampelSize, int TargetFreq, const sf::Int16* Data);
    bool StartBitTest();
    std::string RecorderLoop();
    void StartRecording();
    void StopRecording();
    bool DTMFTest(int LowFreq, int HighFreq);
    void PlaybackTest();
    sf::SoundBufferRecorder recorder;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    const sf::Int16* samples;
    std::size_t samplecount;
    int SamplingRate = 44100;
    double BackgroundNoiseCap = 20.0;
};

#endif // ACK_RECEIVER_H
