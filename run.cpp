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

void Run::Menu(int v)
{
    switch(v)
    {
        case 0:
        play(x,y);
        x=0;
        y=0;
        updatewasd();
        break;

        case 1:
        replay();
        break;

        case 2:
        play(0,-8);
        break;

        case 3:
        play(-8,0);
        break;

        case 4:
        abort();
        break;

        case 5:
        c='e';
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
