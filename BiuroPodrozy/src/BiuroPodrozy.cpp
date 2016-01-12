#include "BiuroPodrozy.h"
#include "Wczasy.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <stdlib.h>
using namespace std;

BiuroPodrozy::BiuroPodrozy(char *sciezka, char *plik_wyjsciowy, char *rodzaj, int dlugosc, float cena, struct tm data, int liczbaWycieczek):
    sciezka(sciezka), plik_wyjsciowy(plik_wyjsciowy), rodzaj(rodzaj), dlugosc(dlugosc), cena(cena), data(data), liczbaWycieczek(0){}

BiuroPodrozy::~BiuroPodrozy(){
    liczbaWycieczek=0;
    for (unsigned int i=0; i<lista_wycieczek.size(); i++)
        delete lista_wycieczek[i];
}

void BiuroPodrozy::zwiekszLicznikWycieczek(){
    liczbaWycieczek++;
}

int BiuroPodrozy::getIloscWycieczek(){
    return liczbaWycieczek;
}

//Funkcja sprawdzajaca, czy dany plik opisuje wycieczke objazdowa czy wczasy i dodajaca odpowiedni wskaznik do wektora wycieczek
void BiuroPodrozy::interpretujDane(string zawartosc){

vector <char*> dane;
char *cstr = new char[zawartosc.length()+1];
char *pch;
string pomocniczy;
Wczasy *wskaznik_wczasy;
WycieczkaObjazdowa *wskaznik_objazd;

    strcpy(cstr, zawartosc.c_str());
    pch = strtok (cstr," [], .-");     //podzielenie zawartosci pliku na tokeny
    while (pch != NULL){
        dane.push_back(pch);    //umieszczenie kazdego tokena w wektorze 'dane'
        pch = strtok (NULL, "[], .-");
    }
    pomocniczy=dane.at(0);
//sprawdzenie, czy mamy do czynienia z wycieczka objazdowa czy z wczasami
    if(pomocniczy=="WP:"){
            wskaznik_wczasy=this->tworzWczasy(dane);
            lista_wycieczek.push_back(wskaznik_wczasy);
    }
    else if (pomocniczy=="WO:") {
            wskaznik_objazd=this->tworzObjazdowke(dane);
            lista_wycieczek.push_back(wskaznik_objazd);
    }
    else cout<<" Wykryto plik z nieznanym typem wycieczki"<<endl;

    delete cstr;
}

//funkcja czytajaca wszystkie pliki z ofertami w danym folderze
void BiuroPodrozy::czytajPliki(){

struct dirent *plik;  //korzystanie z biblioteki POSIX
DIR *sciezka;

    if((sciezka = opendir(this->sciezka))) {    //otworzenie katalogu z ofertami
        while((plik = readdir(sciezka))){
             string zawartosc_pliku;

             char pelna_sciezka[100];
             strcpy(pelna_sciezka,this->sciezka);
             strcat(pelna_sciezka,plik->d_name);

             ifstream nowyPlik;
             nowyPlik.open(pelna_sciezka);   //otworzenie pliku
             while(nowyPlik.good()){
                getline(nowyPlik, zawartosc_pliku);
                this->interpretujDane(zawartosc_pliku);
             }
             nowyPlik.close();
          }
          closedir( sciezka );
    }
    else{
        printf( "Blad otwarcia sciezki do katalogu!");
        exit(0);
    }
}

//Funkcja tworzaca i zwracajaca wskaznik do nowych wczasow
Wczasy* BiuroPodrozy::tworzWczasy(vector <char*> opis){

     Wczasy *wskaznik_wczasy;
     string nazwa;
     struct tm data_rozp;
     int dlugosc;
     string destynacja_miasto;
     string destynacja_kraj;
     float koszt_wycieczki;
     float koszt_autokar;
     float koszt_samolot;
     float koszt_wlasny;

    nazwa.assign(opis.at(1));
    try{
        for (int i=2; i<6; i++){
            if (atoi(opis.at(i))==0) throw 1;
        }
        data_rozp.tm_year=atoi(opis.at(2));
        data_rozp.tm_mon=atoi(opis.at(3));
        data_rozp.tm_mday=atoi(opis.at(4));
        dlugosc=atoi(opis.at(5));
    }
    catch (int wyjatek){
        cout<<"Zly format daty lub dlugosc turnusu jednych z wczasow. Te wczasy zostana pominiete!"<<endl;
        return NULL;
    }
    destynacja_miasto.assign(opis.at(6));
    destynacja_kraj.assign(opis.at(7));
    try{
        if (atoi(opis.at(8))==0) throw 1;
        koszt_wycieczki=atoi(opis.at(8));
    }
    catch(int wyjatek){
        cout<<"wykryto blad w cenie jednych z wczasow!"<<endl;
        return NULL;
    }
    try{
        for(unsigned int i=9; i<opis.size(); i=i+2){
            if (atoi(opis.at(i+1))==0) throw 1;
            string pomocniczy=opis.at(i);

            if (pomocniczy=="Autokar") {
                koszt_autokar=atof(opis.at(i+1));
            }else if (pomocniczy=="Samolot") {
                koszt_samolot=atof(opis.at(i+1));
            }else if (pomocniczy=="Wlasny") {
                koszt_wlasny=atof(opis.at(i+1));
            }else throw 2;
        }
    }
    catch(int wyjatek){
        if (wyjatek==1) cout<<"Zla cena ktoregos ze srodkow transportu! Te wczasy zostana pominiete!"<<endl;
        if (wyjatek==2) cout<<"Zly rodzaj transportu! Te wczasy zostana pominiete!"<<endl;
        return NULL;
    }

   wskaznik_wczasy=new Wczasy(nazwa, data_rozp, dlugosc, destynacja_miasto, destynacja_kraj, koszt_wycieczki, koszt_autokar, koszt_samolot, koszt_wlasny);
   return wskaznik_wczasy;
}

//Funkcja tworzaca i zwracajaca wskaznik do nowych wczasow
WycieczkaObjazdowa* BiuroPodrozy::tworzObjazdowke(vector <char*> opis){

    WycieczkaObjazdowa *wskaznik;
    string nazwa;
    struct tm data_rozp;
    struct tm data_zak;
    float koszt_wyc;
    string dojazd;
    vector<string>lista_miast;
    set<string>lista_krajow;
    string ostatni_kraj;

    nazwa.assign(opis.at(1));
    try{
        for (int i=2;i<8;i++){
            if (atoi(opis.at(i))==0) throw 1;
        }
        data_rozp.tm_year=atoi(opis.at(2));
        data_rozp.tm_mon=atoi(opis.at(3));
        data_rozp.tm_mday=atoi(opis.at(4));
        data_zak.tm_year=atoi(opis.at(5));
        data_zak.tm_mon=atoi(opis.at(6));
        data_zak.tm_mday=atoi(opis.at(7));
    }
    catch (int wyjatek){
        cout<<"Zly format daty! Ta objazdowka zostaje pominieta!"<<endl;
        return NULL;
    }
    for (unsigned int i=8; i<(opis.size()-1); i=i+2){
        if (atoi(opis.at(i))==0){
            string pomoc=opis.at(i);
            string pomoc2=opis.at(i+1);
            lista_miast.push_back(pomoc);
            lista_krajow.insert(pomoc2);
        }else{
            ostatni_kraj.assign(opis.at(i-1));
            try{
                if (atoi(opis.at(i))==0) throw 1;
                koszt_wyc=atof(opis.at(i));
            }
            catch(int wyjatek){
                return NULL;
            }
            try{
                string pomocniczy=opis.at(i+1);
                if (pomocniczy=="Autokar") {
                    dojazd.assign(opis.at(i+1));
                }else if (pomocniczy=="Samolot") {
                    dojazd.assign(opis.at(i+1));
                }else if (pomocniczy=="Wlasny") {
                    dojazd.assign(opis.at(i+1));
                }else throw 1;
            }
            catch(int wyjatek){
                cout<<"zly rodzaj transportu. Ta objazdowka zostaje pominieta!"<<endl;
                return NULL;
            }
        }
    }

    wskaznik=new WycieczkaObjazdowa(nazwa, data_rozp, koszt_wyc, dojazd, data_zak, lista_miast, lista_krajow, ostatni_kraj);
    return wskaznik;
}

void BiuroPodrozy::szukajWycieczek(){
    if (strcmp(this->rodzaj,"o")==0) {
        this->szukajObjazdowek();
    }
    if (strcmp(this->rodzaj,"p")==0){
        this->szukajWczasow();
    }
    if (strcmp(this->rodzaj,"l")==0){
        this->szukajObjazdowek();
    }
    if (strcmp(this->rodzaj,"d")==0){
        this->szukajObjazdowek();
        this->szukajWczasow();
    }
}


void BiuroPodrozy::szukajWczasow(){
    for (unsigned int i=0;i<lista_wycieczek.size();i++){
        Wczasy *pd;
        pd=dynamic_cast<Wczasy*>(lista_wycieczek[i]);
        if (pd!=NULL) pd->sprawdz(this);
    }//koniec petli sprawdzajacej wszystkie elementy wektora
}

void BiuroPodrozy::szukajObjazdowek(){
     for (unsigned int i=0;i<lista_wycieczek.size();i++){
        WycieczkaObjazdowa *pd;
        pd=dynamic_cast<WycieczkaObjazdowa*>(lista_wycieczek[i]);
        if (pd!=NULL) pd->sprawdz(this);
     }
}
