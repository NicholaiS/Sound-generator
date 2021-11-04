#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <math.h>
#include "run.h"
#include "sound_generator.h"
#include <unistd.h>
#include "encoder.h"

int main()
{
    //Run a;
    //a.run();
    encoder e;
    std::cout << e.decode("1110000000") << std::endl;
    std::cout << e.decodecheck<< std::endl;
}
