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
/*Funkcja sprawdzajaca, czy dany plik opisuje wycieczke objazdow¹ czy wczasy */
void BiuroPodrozy::interpretujDane(string zawartosc){

char *cstr = new char[zawartosc.length()+1];

    strcpy(cstr, zawartosc.c_str());

    switch(cstr[1]){
    case 'P':
        cout<<"Mamy wczasy"<<endl;
        //biuro.tworzWczasy(&cstr);
        break;
    case 'O':
        cout<<"Mamy objazd"<<endl;
        break;
    default:
        cout<<"Niepoprawny format pliku!! Program zaraz wybuchnie!"<<endl;
        break;
    }

    delete [] cstr;
}

void BiuroPodrozy::czytajPlik(){


struct dirent * plik;  //korzystanie z biblioteki POSIX
DIR * sciezka;
BiuroPodrozy biuro;

    if((sciezka = opendir("oferty/"))) {    //otworzenie katalogu z ofertami
        while((plik = readdir(sciezka))){

            // puts(plik->d_name);               //wypisanie nazwy znalezionego pliku

             string zawartosc_pliku;

             char pelna_sciezka[40] = "oferty/";
             strcat(pelna_sciezka,plik->d_name);

             ifstream NowyPlik;
             NowyPlik.open(pelna_sciezka);   //otworzenie pliku

                while(NowyPlik.good()){

                cout <<"Jestem w pliku!!"<<endl;
                getline(NowyPlik, zawartosc_pliku);
                cout<<zawartosc_pliku<<endl;
                biuro.interpretujDane(zawartosc_pliku);
                }

             NowyPlik.close();

          }
          closedir( sciezka );
    }
    else
         printf( "Blad otwarcia sciezki do katalogu!");


}

