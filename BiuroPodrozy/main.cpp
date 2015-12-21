#include <iostream>
#include "BiuroPodrozy.h"
#include <vector>
using namespace std;

int main(int argc, char **argv){

    //if (argc==7){
    cout<<argv[1]<<endl;
    cout << "Hello world!" << endl;
    BiuroPodrozy biuro;
    biuro.czytajPlik(argv[1]);
    cout<<biuro.lista_wczasow.size()<<" tyle w mainie"<<endl;
    cout<<biuro.lista_objazdowek.size()<<" tyle w mainie obj"<<endl;

    struct tm data;
    data.tm_mday=12;
    data.tm_mon=11;
    data.tm_year=2015;

    biuro.szukajWczasow(data, 14, 3000);
   /* }else
        cout<<"Zla ilosc argumentow wywolania programu!!"<<endl; */

    return 0;
}

