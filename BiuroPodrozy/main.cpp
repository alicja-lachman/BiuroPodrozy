#include <iostream>
#include "BiuroPodrozy.h"
#include <vector>
using namespace std;

int main(int argc, char **argv){

    if (argc==7){
    cout<<argv[1]<<endl;
    cout << "Hello world!" << endl;
    BiuroPodrozy biuro;
    biuro.czytajPlik(argv[1]);
    cout<<biuro.lista_wczasow.size()<<" tyle w mainie"<<endl;
    cout<<biuro.lista_objazdowek.size()<<" tyle w mainie obj"<<endl;

    }else
        cout<<"Zla ilosc argumentow wywolania programu!!"<<endl;

    return 0;
}

