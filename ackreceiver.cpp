#include "ackreceiver.h"

Response::Response()
{

}

void Response::FindMic()
{
    if(!sf::SoundBufferRecorder::isAvailable())
    {
        std::cout << "No microphone is available." << std::endl;
    }
    else
    {
        std::cout << "Microphone found" << std::endl;
    }
}

void Response::StartRecording()
{
    unsigned int sampleRate = 44100;
    recorder.start(sampleRate);
    //std::cout << "Recording ..." << std::endl;        //useful for testing the timing
}

void Response::StopRecording()
{
    recorder.stop();
    buffer = recorder.getBuffer();
    sound.setBuffer(buffer);
    samples = buffer.getSamples();
    samplecount = buffer.getSampleCount();
    //std::cout << "Recording stopped" << std::endl;    //useful for testing timing
}

double Response::GoertzelAlgorithm(int SampelSize, int TargetFreq, const sf::Int16* Data)
{
    int k;
    double DoubleSampleSize;
    double omega, sine, cosine, coeff, s_n, s_nMinus1, s_nMinus2, magnitude, real, imag;

    double scalingFactor = SampelSize / 2.0;

    DoubleSampleSize = (double) SampelSize;
    k = (int) (0.5 + ((DoubleSampleSize * TargetFreq) / SamplingRate));
    omega = (2.0 * M_PI * k) / DoubleSampleSize;
    sine = sin(omega);
    cosine = cos(omega);
    coeff = 2.0 * cosine;
    s_n = 0;
    s_nMinus1 = 0;
    s_nMinus2 = 0;


    for(int i = 0; i < SampelSize; i++)
    {
        s_n = Data[i] + coeff * s_nMinus1 - s_nMinus2;
        s_nMinus2 = s_nMinus1;
        s_nMinus1 = s_n;
    }
    real = (s_nMinus1 - s_nMinus2 * cosine) / scalingFactor;
    imag = (s_nMinus2 * sine) / scalingFactor;

    magnitude = sqrtf(real*real + imag*imag);

    return magnitude;
}

bool Response::DTMFTest(int LowFreq, int HighFreq)
{
    int input = LowFreq + HighFreq;
    double DTMF1Mag = GoertzelAlgorithm(samplecount, 697, samples) +
            GoertzelAlgorithm(samplecount, 1209, samples);
    double DTMF9Mag = GoertzelAlgorithm(samplecount, 852, samples) +
            GoertzelAlgorithm(samplecount, 1477, samples);
    double DTMFDMag = GoertzelAlgorithm(samplecount, 941, samples) +
            GoertzelAlgorithm(samplecount, 1633, samples);

    switch(input)
    {
    case 1906:
        if(DTMF1Mag > DTMF9Mag && DTMF1Mag > DTMFDMag && DTMF1Mag > BackgroundNoiseCap)
            return true;
        else
            return false;
        break;

    case 2329:
        if(DTMF9Mag > DTMF1Mag && DTMF9Mag > DTMFDMag && DTMF9Mag > BackgroundNoiseCap)
            return true;
        else
            return false;
        break;

    case 2574:
        if(DTMFDMag > DTMF1Mag && DTMFDMag > DTMF9Mag && DTMFDMag > BackgroundNoiseCap)
            return true;
        else
            return false;
        break;

    default:
        return false;
        break;
    }
}

int Response::ResponseRecognition()
{
//    if(StartBitTest())
//    {
//        std::cout << "Startbit fundet" << std::endl;
            StartRecording();
            usleep(150000);

            StopRecording();

            if(DTMFTest(697, 1209))
            {
                return 1;
            }
            else if(DTMFTest(852, 1477))
            {
                return 2;
            }
            else if(DTMFTest(941, 1633))
            {
                return 3;
            }
            else
            {
                return 0;
            }
//    }
}

//TEST FUNKTIONER og startbitstest:

void Response::PlaybackTest()
{
    recorder.stop();
    buffer = recorder.getBuffer();
    sound.setBuffer(buffer);
    samples = buffer.getSamples();
    samplecount = buffer.getSampleCount();
    std::cout << "Playing back ..." << std::endl;
    sound.play();
    std::cout << "Done ..." << std::endl;
}

bool Response::StartBitTest() //implemented in case a startbit was used, it wasn't
{
    std::cout << "Waiting for start bit" << std::endl;
    double DTMF1Mag;
    double DTMF9Mag;
    double DTMFDMag;
    do
    {
        usleep(100000);
        StopRecording();
        //DTMFTest For Start Bittet:
        DTMF1Mag = GoertzelAlgorithm(samplecount, 697, samples) + GoertzelAlgorithm(samplecount, 1209, samples);
        DTMF9Mag = GoertzelAlgorithm(samplecount, 852, samples) + GoertzelAlgorithm(samplecount, 1477, samples);
        DTMFDMag = GoertzelAlgorithm(samplecount, 941, samples) + GoertzelAlgorithm(samplecount, 1633, samples);
        if(DTMF1Mag > DTMF9Mag && DTMF1Mag > DTMFDMag && DTMF1Mag > BackgroundNoiseCap)
        {
            return true;
            break;
        }

        sound.resetBuffer();
        StartRecording();
    } while(1);
}
