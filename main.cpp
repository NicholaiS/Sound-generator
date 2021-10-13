#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <math.h>
#include "sound_generator.h"
#include <unistd.h>

int main()
{
    SoundGenerator a;
    a.PlaySound(777,1600,0.1);
//    a.Run();

//    Det her er en test

    return 0;
}
