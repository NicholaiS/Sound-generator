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
    a.SetDuration(1);
    a.Run();

    return 0;
}
