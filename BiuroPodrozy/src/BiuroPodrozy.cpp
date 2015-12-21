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
    pch = strtok (cstr," [],.-");     //podzielenie zawartosci pliku na tokeny

    while (pch != NULL){

        printf ("%s\n",pch);
        dane.push_back(pch);    //umieszczenie kazdego tokena w wektorze 'dane'
        pch = strtok (NULL, "[] ,.-");
    }

    pomocniczy=dane.at(0);
//sprawdzenie, czy mamy do czynienia z wycieczka objazdowa czy z wczasami
    if(pomocniczy=="WP:"){
        cout<<"To beda wczasy!!"<<endl;
        this->tworzWczasy(dane);

    }
    else if (pomocniczy=="WO:"){
        cout<<"Mamy objazdwoke!"<<endl;
        this->tworzObjazdowke(dane);
    }else
        cout<<"cos sknocone"<<endl;
     cout<<"nasz wektorek"<<lista_wczasow.size()<<endl;
     cout<<"nasz drugi wektorek"<<lista_objazdowek.size()<<endl;
    delete pch;


}

void BiuroPodrozy::czytajPlik(char *folder){

struct dirent * plik;  //korzystanie z biblioteki POSIX
DIR * sciezka;


    if((sciezka = opendir(folder))) {    //otworzenie katalogu z ofertami
        while((plik = readdir(sciezka))){

             string zawartosc_pliku;

             char pelna_sciezka[100];
             strcpy(pelna_sciezka,folder);
             strcat(pelna_sciezka,plik->d_name);

             ifstream NowyPlik;
             NowyPlik.open(pelna_sciezka);   //otworzenie pliku

             while(NowyPlik.good()){

                cout <<"Jestem w pliku!!"<<endl;
                getline(NowyPlik, zawartosc_pliku);
                cout<<zawartosc_pliku<<endl;
                this->interpretujDane(zawartosc_pliku);
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

}
this->lista_wczasow.push_back(noweWczasy);
}

//Funkcja dodajaca objazdowke z pliku do wektora objazdowek
void BiuroPodrozy::tworzObjazdowke(vector <char*> opis){
    WycieczkaObjazdowa nowaObjazdowka;

    strcpy(nowaObjazdowka.nazwa,opis.at(1));
    nowaObjazdowka.data_rozpoczecia.tm_year=atoi(opis.at(2));
    nowaObjazdowka.data_rozpoczecia.tm_mon=atoi(opis.at(3));
    nowaObjazdowka.data_rozpoczecia.tm_mday=atoi(opis.at(4));
    nowaObjazdowka.data_zakonczenia.tm_year=atoi(opis.at(5));
    nowaObjazdowka.data_zakonczenia.tm_mon=atoi(opis.at(6));
    nowaObjazdowka.data_zakonczenia.tm_mday=atoi(opis.at(7));

    int ilosc_danych=opis.size();

    for (int i=8; i<ilosc_danych-1; i++){

        if (atoi(opis.at(i))==0){

            string pomoc=opis.at(i);
            string pomoc2=opis.at(i+1);
            nowaObjazdowka.lista_miast.push_back(pomoc);
            nowaObjazdowka.lista_krajow.push_back(pomoc2);
        }else{

            nowaObjazdowka.kosztWycieczki=atoi(opis.at(i));
            BiuroPodrozy::rodzajTransportu2(opis, i+1, nowaObjazdowka);
        }
    }
this->lista_objazdowek.push_back(nowaObjazdowka);
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
//zamienic na wirtualnaaaaa
 void BiuroPodrozy::rodzajTransportu2(vector<char*>opis,int i, WycieczkaObjazdowa &objazdowka){
    string pomocniczy=opis.at(i);
 if (pomocniczy=="Autokar") {
    strcpy(objazdowka.dojazd,opis.at(i));
 }else if (pomocniczy=="Samolot") {
    strcpy(objazdowka.dojazd,opis.at(i));

 }else if (pomocniczy=="Wlasny") {
    strcpy(objazdowka.dojazd,opis.at(i));

 }else cout<<"Cos sknocone!"<<endl;
}

void BiuroPodrozy::szukajWczasow(struct tm data, int dlugosc, float cena){

    for (unsigned int i=0;i<lista_wczasow.size();i++){
        if ((lista_wczasow[i].data_rozpoczecia.tm_year) >= data.tm_year) {
            if (((lista_wczasow[i].data_rozpoczecia.tm_mon) > data.tm_mon)     //Bardzo dlugi warunek dla miesiace
            || ((lista_wczasow[i].data_rozpoczecia.tm_mon) == data.tm_mon
            && (lista_wczasow[i].data_rozpoczecia.tm_mday) >= data.tm_mday)){
                cout<<"yay";
                if((lista_wczasow[i].dlugosc_turnusu) <= dlugosc){
                    if ((lista_wczasow[i].kosztWycieczki)+(lista_wczasow[i].koszt_autokar)<=cena){
                        //jak tak to wpis
                    } //koniec warunku dla autokaru
                    if ((lista_wczasow[i].kosztWycieczki)+(lista_wczasow[i].koszt_samolot)<=cena){
                        //jak tak to wpis
                    } //koniec warunku dla samolotu
                    if ((lista_wczasow[i].kosztWycieczki)+(lista_wczasow[i].koszt_samolot)<=cena){
                    } //koniec warunku dla dojazdu wlasnego

                }//koniec petli sprawdzajacej dlugosc turnusu
            } //koniec petli sprawdzajacej miesiac (bardzo długi warunek)
        } //koniec petli sprawdzajacej rok


    }


}

