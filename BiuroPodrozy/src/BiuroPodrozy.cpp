#include "BiuroPodrozy.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <io.h>

#include <dirent.h>
using namespace std;

BiuroPodrozy::BiuroPodrozy()
{
    //ctor
}

BiuroPodrozy::~BiuroPodrozy()
{
    //dtor
}

void BiuroPodrozy::czytajPlik(){


struct dirent * plik;
    DIR * sciezka;



    if(( sciezka = opendir("oferty/") ) ) {
        while(( plik = readdir( sciezka ) ) ){
             puts( plik->d_name );
              string zawartosc_pliku;
 char pelna_sciezka[40] = "oferty/";
strcat(pelna_sciezka,plik->d_name);

   ifstream NowyPlik;
   NowyPlik.open(pelna_sciezka);

   while(NowyPlik.good())
        {
            cout <<"jestem tu!!"<<endl;
        getline(NowyPlik, zawartosc_pliku);
        cout<<zawartosc_pliku<<endl;
        }

   NowyPlik.close();
        }
        closedir( sciezka );
    }
    else
         printf( "! wywo�uj�c funkcj� opendir(%s) pojawi� si� b��d otwarcia strumienia dla danej �cie�ki, mo�e nie istnieje, lub podano �cie�k� pust�\n");


}
