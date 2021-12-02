#include "run.h"
#include <ncurses.h>

Run::Run(){}

void Run::run(){
    // ncurses opsætning
    initscr();
    noecho();
    curs_set(0);

    // bruger skærmstørrelsen til a konfigurere mit vindue
    int ymax, xmax;
    getmaxyx(stdscr,ymax,xmax);

    //indstiller mine vinduer
    printw("WASD til bevægelse for robotten, piletaster for menuen, enter for vælg");
    refresh();
    txtwin = newwin(5,xmax-12,ymax-7,2);
    styrwin = newwin(8,15,1,2);
    menuwin = newwin(20,25,1,xmax-35);
    box(txtwin,0,0);
    box(styrwin,0,0);
    box(menuwin,0,0);
    mvwprintw(txtwin,1,1,"her kommer der til at stå status på afsendelse og acknowledgments");
    mvwprintw(styrwin,3,7,"w");
    mvwprintw(styrwin,4,6,"asd");
    wrefresh(menuwin);
    wrefresh(txtwin);
    wrefresh(styrwin);

    // slår keypad til
    keypad(menuwin,true);


    do{
    updatemenu();
    c = wgetch(menuwin);
    inputswitch(c);

    wrefresh(menuwin);
    wrefresh(txtwin);
    wrefresh(styrwin);
    } while(c != 'e');

    //sluk
    delwin(menuwin);
    delwin(txtwin);
    delwin(styrwin);
    endwin();
}

void Run::updatewasd()
{
    if(y>0){
        mvwprintw(styrwin,2,7,"%d",y);
        mvwprintw(styrwin,5,7,"  ");
    } else if(y<0){
        mvwprintw(styrwin,5,7,"%d",abs(y));
        mvwprintw(styrwin,2,7,"  ");
    } else if(y==0){
        mvwprintw(styrwin,5,7,"  ");
        mvwprintw(styrwin,2,7,"  ");
    }

    if(x>0){
        mvwprintw(styrwin,4,10,"%d",x);
        mvwprintw(styrwin,4,4,"  ");
    }else if(x<0){
        mvwprintw(styrwin,4,4,"%d",abs(x));
        mvwprintw(styrwin,4,10,"  ");
    }else if(x==0){
        mvwprintw(styrwin,4,4,"  ");
        mvwprintw(styrwin,4,10,"  ");
    }
}

void Run::updatemenu()
{
    for(int i=0;i<6;i++){
        if(i==v){
            wattron(menuwin,A_REVERSE);
            mvwprintw(menuwin,i+1,1,valg[i].c_str());
            wattroff(menuwin,A_REVERSE);
        } else {
            mvwprintw(menuwin,i+1,1,valg[i].c_str());
        }
    }
}

void Run::updatetxt(message m){
    wclear(txtwin);
    box(txtwin,0,0);
    displaytxt(m,0);
    displaytxt(second,1);
    displaytxt(third,2);
    third = second;
    second = m;
    wrefresh(txtwin);
}

void Run::displaytxt(message n, int i){
    switch(n)
    {
        case Null:
        mvwprintw(txtwin,i+1,1," - ");
        break;

        case Idle:
        mvwprintw(txtwin,i+1,1,"Waiting for a command");
        break;

        case SPlaying:
        mvwprintw(txtwin,i+1,1,"Sending instructions...");
        break;

        case DPlaying:
        mvwprintw(txtwin,i+1,1,"Instructions sent, waiting for a response");
        break;

        case Response1:
        mvwprintw(txtwin,i+1,1,"Instructions sent with no problems");
        break;

        case Response2:
        mvwprintw(txtwin,i+1,1,"Instructions not understood, please move closer and replay");
        break;

        case Response3:
        mvwprintw(txtwin,i+1,1,"Instructions not understood, please replay");
        break;

        case NoResponse:
        mvwprintw(txtwin,i+1,1,"Response not understood, please replay if the robot hasn't moved");
        break;

        case Instructions:
        mvwprintw(txtwin,i+1,1,"WASD: move robot, up/down: move in menu, enter: chose in menu");
        break;

        default:
        break;
    }
}

void Run::Menu(int v)
{
    switch(v)
    {
        case 0:
        updatetxt(SPlaying);
        play(x,y);
        x=0;
        y=0;
        updatetxt(DPlaying);
        usleep(2300000);
        checkresponse();
        //mvwprintw(txtwin,1,1,senest.c_str());  //kan være nyttigt til at teste
        updatewasd();
        break;

        case 1:
        replay();
        break;

        case 2:
        updatetxt(SPlaying);
        play(0,-8);
        updatetxt(DPlaying);
        checkresponse();
        break;

        case 3:
        updatetxt(SPlaying);
        play(-8,0);
        updatetxt(DPlaying);
        checkresponse();
        break;

        case 4:
        updatetxt(Instructions);
        startbit();
        break;

        case 5:
        c='e';
        break;
    }
}

void Run::checkresponse(){
    int i;

    for(int j=0; j<7;j++){
        i=ResponseRecognition();
        if(i!=0){
            j=8;
        }
    }

    switch(i)
    {
     case 0:
     updatetxt(NoResponse);
     break;

     case 1:
     updatetxt(Response1);
     break;

     case 2:
     updatetxt(Response2);
     break;

     case 3:
     updatetxt(Response2);
     break;
    }
}

void Run::inputswitch(int i){
    switch(i){
        case 'w':
        if(y!=7){
        y++;
        updatewasd();
        }
        break;

        case 's':
        if(abs(y)!=7||y==7){
        y--;
        updatewasd();
        }
        break;

        case 'd':
        if(x!=7){
        x++;
        updatewasd();
        }
        break;

        case 'a':
        if(abs(x)!=7||x==7){
        x--;
        updatewasd();
        }
        break;

        case KEY_UP:
        if(v!=0){
        v--;
        updatemenu();
        }
        break;

        case KEY_DOWN:
        if(v!=5){
        v++;
        updatemenu();
        }
        break;

        case 10:
        Menu(v);
        break;

        default:
        break;
    }
}
