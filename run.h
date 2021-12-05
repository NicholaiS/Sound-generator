#ifndef RUN_H
#define RUN_H
#include "packetsender.h"
#include "ackreceiver.h"
#include <ncurses.h>
#include <string>

enum message {Null,Idle,SPlaying,DPlaying,
              Response1,Response2,Response3,
              NoResponse,Instructions};

class Run : packetsender, Response
{
public:
    Run();
    void run();
private:
    void Menu(int v);
    void updatemenu();
    void updatewasd();
    void updatetxt(message m);
    void displaytxt(message n, int i);
    void inputswitch(int i);
    void checkresponse();
    int v=0;
    int x=0;
    int y=0;
    int c;
    message second, third;
    std::string valg[6] = {"Play","Replay","Slower","Faster","Instructions","Close"};
    WINDOW * txtwin;
    WINDOW * controlwin;
    WINDOW * menuwin;
};

#endif // RUN_H
