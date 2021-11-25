#include "packetsender.h"

packetsender::packetsender()
{

}

void packetsender::play(int x, int y){
    std::string strx=std::bitset<4>(x).to_string();
    std::string stry=std::bitset<4>(y).to_string();
    std::string strxy=strx+stry;
    senest=encode(strxy);

    setduration(0.02);
    PlaySingle(697,1209);
    setduration(0.2);
    PlaySequence(senest);
    PlaySingle(770,1336);
}

void packetsender::replay(){
    PlaySingle(697,1209);
    PlaySequence(senest);
    PlaySingle(770,1336);

}

void packetsender::stopbit(){
    PlaySingle(770,1336);
    PlaySingle(770,1336);
}
