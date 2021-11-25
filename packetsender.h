#ifndef PACKETSENDER_H
#define PACKETSENDER_H
#include "sound_generator.h"
#include "encoder.h"
#include <bitset>

class packetsender : SoundGenerator, encoder
{
public:
    packetsender();
    void play(int x, int y);
    void replay();
    void stopbit();
private:
    std::string senest;
};

#endif // PACKETSENDER_H
