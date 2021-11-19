#ifndef RUN_H
#define RUN_H
#include "packetsender.h"
#include <ncurses.h>
#include <string>


class Run : packetsender
{
public:
    Run();
    void run();
private:
    void Menu(int v);
    void updatemenu();
    void updatewasd();
    void inputswitch(int i);
    int v=0;
    int x=0;
    int y=0;
    int c;
    std::string valg[6] = {"Play","Replay","Slower","Faster","Stopbit","Close"};
    WINDOW * txtwin;
    WINDOW * styrwin;
    WINDOW * menuwin;
};

#endif // RUN_H
