#include <iostream>
#include "BiuroPodrozy.h"
#include <vector>
using namespace std;

int main(int argc, char **argv){

    //if (argc==7){
    cout<<argv[1]<<endl;
    cout << "Hello world!" << endl;
    BiuroPodrozy biuro;
   // biuro.czytajPlik(argv[1]);


    struct tm data;
    data.tm_mday=12;
    data.tm_mon=12;
    data.tm_year=2015;

    data=biuro.obliczDate(30,data,40);
    cout<<data.tm_mday<<"."<<data.tm_mon<<"."<<data.tm_year<<endl;
   //biuro.szukajWczasow(data, 14, 2300);
   /* }else
        cout<<"Zla ilosc argumentow wywolania programu!!"<<endl; */

    return 0;
}

