#include "encoder.h"
#include <string>
#include <iostream>

encoder::encoder()
{

}

std::string encoder::encode(std::string i){
if(encheckstring(i)){

    std::string sh1;
    std::string sh2;

    std::string fs;

    for(int j=0; j<(2*n);j++){
    if(j<n){
        sh1+=i[j];
    } else {
        sh2+=i[j];
    }
    }

    for(int j=0; j<(n*n);j++){
        if(sh1==dataword[j]){
            fs+=kodeword[j];
        }
    }

    for(int j=0; j<(n*n);j++){
        if(sh2==dataword[j]){
            fs+=kodeword[j];
        }
    }
    return fs;

} else {
    std::cout << "string ikke 8 lang eller 1/0" << std::endl;
    return "string ikke 8 lang eller 1/0";
}
}

std::string encoder::decode(std::string i){

    if(decheckstring(i)){
    std::string sh1, sh2, fs;

    int tæl=0;

    for(int j=0; j<(2*k);j++){
    if(j<k){
        sh1+=i[j];
    } else {
        sh2+=i[j];
    }
    }

    for(int j=0; j<(n*n);j++){
        if(sh1==kodeword[j]){
            fs+=dataword[j];
        } else {tæl++;}
    }

    for(int j=0; j<(n*n);j++){
        if(sh2==kodeword[j]){
            fs+=dataword[j];
        } else {tæl++;}
    }

    fejl=tæl-(n*n*2-2);

    if(fejl==0){
    return fs;
    decodecheck=true;
    } else {
        std::string fejlstr = sh1.substr(0,4);
        fejlstr += sh2.substr(0,4);
        return fejlstr;
        decodecheck=false;
    }

}   std::cout << "string ikke 10 lang eller 1/0" << std::endl;
    return "string ikke 10 lang eller 1/0";
}

bool encoder::encheckstring(std::string i){
    bool tjek1=false, tjek2=false;
    if(i.size()==(2*n)){
        tjek1=true;
    }

    int h=0;
    for(int j=0; j<(2*n);j++){

        if(i[j]=='0'||i[j]=='1'){
            h++;
        }
    }

    if(h==(2*n)){
        tjek2=true;
    }

    if(tjek1&&tjek2){
        return true;
    } else return false;
}

bool encoder::decheckstring(std::string i){
    bool tjek1=false, tjek2=false;
    if(i.size()==(2*k)){
        tjek1=true;
    }

    int h=0;
    for(int j=0; j<(2*k);j++){

        if(i[j]=='0'||i[j]=='1'){
            h++;
        }
    }

    if(h==(2*k)){
        tjek2=true;
    }

    if(tjek1&&tjek2){
        return true;
    } else {
        return false;
    }
}
