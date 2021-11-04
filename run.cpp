#include "run.h"

Run::Run(){}

void Run::run(){
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
}

void Run::Movement(direction d)
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
