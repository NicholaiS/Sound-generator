#include "packetsender.h"

packetsender::packetsender()
{

}

void packetsender::play(int x, int y){
    std::string strx=std::bitset<4>(x).to_string();
    std::string stry=std::bitset<4>(y).to_string();
    std::string strxy=strx+stry;

    PlaySequence(startstop(encode(strxy)));
    senest=startstop(encode(strxy));
}

void packetsender::replay(){
    PlaySequence(senest);
}


std::string packetsender::startstop(std::string s){
    std::string str="0";
    str+=s;
    str+="1";
    return str;
}
