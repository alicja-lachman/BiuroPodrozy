#include "BiuroPodrozy.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
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
//zmienic na cos w rodzaju PODZIAlDanych
void BiuroPodrozy::interpretujDane(string zawartosc){

vector <char*> dane;
char *cstr = new char[zawartosc.length()+1];
char * pch;
string pomocniczy;

    strcpy(cstr, zawartosc.c_str());
    printf ("Splitting string \"%s\" into tokens:\n",cstr);
    pch = strtok (cstr," ,.-");     //podzielenie zawartosci pliku na tokeny

    while (pch != NULL){

        printf ("%s\n",pch);
        dane.push_back(pch);    //umieszczenie kazdego tokena w wektorze 'dane'
        pch = strtok (NULL, " ,.-");
    }

    pomocniczy=dane.at(0);
//sprawdzenie, czy mamy do czynienia z wycieczka objazdowa czy z wczasami
    if(pomocniczy=="WP:"){
        cout<<"To beda wczasy!!"<<endl;
        BiuroPodrozy::tworzWczasy(dane);
    }
    else if (pomocniczy=="WO:"){
        cout<<"Mamy objazdwoke!"<<endl;
    }else
        cout<<"cos sknocone"<<endl;

    delete cstr;
    delete pch;
}

void BiuroPodrozy::czytajPlik(){

struct dirent * plik;  //korzystanie z biblioteki POSIX
DIR * sciezka;
BiuroPodrozy biuro;

    if((sciezka = opendir("oferty/"))) {    //otworzenie katalogu z ofertami
        while((plik = readdir(sciezka))){

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

 void BiuroPodrozy::tworzWczasy(vector <char*> opis){
    cout<<"Tworze wczasy!"<<endl;
    cout<<opis.at(3)<<endl;

}

