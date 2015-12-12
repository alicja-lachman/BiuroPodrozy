#include <iostream>
#include "BiuroPodrozy.h"
#include <vector>
using namespace std;

int main()
{


    cout << "Hello world!" << endl;
    BiuroPodrozy biuro;
    biuro.czytajPlik();
    cout<<biuro.lista_wczasow.size()<<" tyle w mainie"<<endl;
    cout<<biuro.lista_objazdowek.size()<<" tyle w mainie obj"<<endl;
    return 0;
}
