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
    int v=0;
    int x=0;
    int y=0;
    std::string valg[4] = {"play","replay","slower","faster"};
    WINDOW * txtwin;
    WINDOW * styrwin;
    WINDOW * menuwin;
};

#endif // RUN_H
