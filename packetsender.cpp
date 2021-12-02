#include "packetsender.h"

packetsender::packetsender()
{

}

void packetsender::play(int x, int y){
    std::string strx=std::bitset<4>(x).to_string();
    std::string stry=std::bitset<4>(y).to_string();
    std::string strxy=strx+stry;
    senest=encode(strxy);

    setduration(0.04);
    PlaySingle(697,1209);
    setduration(0.2);
    usleep(862500);
    PlaySequence(senest);
    //PlaySingle(770,1336); can be used for testing
}

void packetsender::replay(){
    setduration(0.04);
    PlaySingle(697,1209);
    setduration(0.2);
    usleep(862500);
    PlaySequence(senest);
    //PlaySingle(770,1336); can be used for testing
}

// used when testing the startbit
void packetsender::startbit(){
    setduration(0.1);
    PlaySingle(697,1209);
}
