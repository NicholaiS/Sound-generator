#include "packetsender.h"

packetsender::packetsender()
{

}

void packetsender::play(int x, int y){
    std::string strx=std::bitset<4>(x).to_string();
    std::string stry=std::bitset<4>(y).to_string();
    std::string strxy=strx+stry;
    senest=encode(strxy);

    PlaySingle(770,1209);
    PlaySequence(senest);
    PlaySingle(770,1336);
}

void packetsender::replay(){
    PlaySingle(770,1209);
    PlaySequence(senest);
    PlaySingle(770,1336);
}

void packetsender::abort(){
    PlaySingle(852,1336);
    PlaySingle(852,1336);
    PlaySingle(852,1336);
    PlaySingle(852,1336);
    PlaySingle(852,1336);
    PlaySingle(852,1336);
}
