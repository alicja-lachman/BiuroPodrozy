#include <iostream>
#include "BiuroPodrozy.h"
#include <vector>
using namespace std;

int main(int argc, char **argv){

    //if (argc==7){
    cout<<argv[1]<<endl;
    cout << "Hello world!" << endl;
    BiuroPodrozy biuro;
    //biuro.czytajPlik(argv[1]);


    struct tm data;
    data.tm_mday=12;
    data.tm_mon=12;
    data.tm_year=2015;

    struct tm data2;
    data2.tm_mday=12;
    data2.tm_mon=12;
    data2.tm_year=2015;

    cout<<biuro.porownajDate(data,data2)<<endl;
    //biuro.szukajWczasow(data, 14, 2300);
   /* }else
        cout<<"Zla ilosc argumentow wywolania programu!!"<<endl; */

    return 0;
}

