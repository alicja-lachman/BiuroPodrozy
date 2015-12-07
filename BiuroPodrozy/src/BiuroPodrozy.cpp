#include "BiuroPodrozy.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <stdlib.h>
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

    Wczasy noweWczasy;
    strcpy(noweWczasy.nazwa,opis.at(1));
    noweWczasy.data_rozpoczecia.tm_year=atoi(opis.at(2));
    noweWczasy.data_rozpoczecia.tm_mon=atoi(opis.at(3));
    noweWczasy.data_rozpoczecia.tm_mday=atoi(opis.at(4));
    noweWczasy.dlugosc_turnusu=atoi(opis.at(5));
    strcpy(noweWczasy.destynacja_miasto,opis.at(6));
    strcpy(noweWczasy.destynacja_kraj,opis.at(7));
    noweWczasy.kosztWycieczki=atoi(opis.at(8));

    BiuroPodrozy::rodzajTransportu(opis, 9, noweWczasy);

    if (opis.size()>12){
        BiuroPodrozy::rodzajTransportu(opis, 11, noweWczasy);
            if(opis.size()<15){
            cout<<"nie ma wiecej srodkow transportu"<<endl;  //wyjscie z petli dodac
            }else {
            BiuroPodrozy::rodzajTransportu(opis, 13, noweWczasy);
            }
    }//else cout<<"Tylko jeden srodek transportu"<<endl;
    lista_wczasow.push_back(noweWczasy);
}


//dodac zabezpieczenie, jesli wystapi jakis blad to wywiesic flage
 void BiuroPodrozy::rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy){
    string pomocniczy=opis.at(i);
 if (pomocniczy=="Autokar") {
    strcpy(wczasy.dojazd,opis.at(i));
    wczasy.koszt_autokar=atoi(opis.at(i+1));
 }else if (pomocniczy=="Samolot") {
    strcpy(wczasy.dojazd,opis.at(i));
    wczasy.koszt_samolot=atoi(opis.at(i+1));
 }else if (pomocniczy=="Wlasny") {
    strcpy(wczasy.dojazd,opis.at(i));
    wczasy.koszt_wlasny=atoi(opis.at(i+1));
 }else cout<<"Cos sknocone!"<<endl;
}

