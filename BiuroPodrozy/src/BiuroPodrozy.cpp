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
    this->liczbaWycieczek=0;

}

BiuroPodrozy::~BiuroPodrozy(){}

int BiuroPodrozy::podajIlosc(){
    return liczbaWycieczek;
}
//Funkcja sprawdzajaca, czy dany plik opisuje wycieczke objazdowa czy wczasy
void BiuroPodrozy::interpretujDane(string zawartosc){

vector <char*> dane;
char *cstr = new char[zawartosc.length()+1];
char * pch;
string pomocniczy;

    strcpy(cstr, zawartosc.c_str());
    pch = strtok (cstr," [],.-");     //podzielenie zawartosci pliku na tokeny
    while (pch != NULL){
        dane.push_back(pch);    //umieszczenie kazdego tokena w wektorze 'dane'
        pch = strtok (NULL, "[] ,.-");
    }
    pomocniczy=dane.at(0);
//sprawdzenie, czy mamy do czynienia z wycieczka objazdowa czy z wczasami
    if(pomocniczy=="WP:") this->tworzWczasy(dane);
    else if (pomocniczy=="WO:") this->tworzObjazdowke(dane);
    else cout<<" Wykryto plik z nieznanym typem wycieczki"<<endl;

    delete cstr;
    delete pch;
}
//funkcja czytajaca wszystkie pliki z ofertami w danym folderze
void BiuroPodrozy::czytajPliki(char *folder){

struct dirent *plik;  //korzystanie z biblioteki POSIX
DIR *sciezka;

    if((sciezka = opendir(folder))) {    //otworzenie katalogu z ofertami
        while((plik = readdir(sciezka))){
             string zawartosc_pliku;

             char pelna_sciezka[100];
             strcpy(pelna_sciezka,folder);
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

//Funkcja tworzaca nowe wczasy i dodajace je do wektora wczasow
void BiuroPodrozy::tworzWczasy(vector <char*> opis){

    Wczasy noweWczasy;
    strcpy(noweWczasy.nazwa,opis.at(1));
    try{
        for (int i=2; i<6; i++){
            if (atoi(opis.at(i))==0) throw 1;
        }
        noweWczasy.data_rozpoczecia.tm_year=atoi(opis.at(2));
        noweWczasy.data_rozpoczecia.tm_mon=atoi(opis.at(3));
        noweWczasy.data_rozpoczecia.tm_mday=atoi(opis.at(4));
        noweWczasy.dlugosc_turnusu=atoi(opis.at(5));
    }
    catch (int wyjatek){
        cout<<"Zly format daty lub dlugosc turnusu jednych z wczasow. Te wczasy zostana pominiete!"<<endl;
        return;
    }
    strcpy(noweWczasy.destynacja_miasto,opis.at(6));
    strcpy(noweWczasy.destynacja_kraj,opis.at(7));
    try{
        if (atoi(opis.at(8))==0) throw 1;
        noweWczasy.kosztWycieczki=atoi(opis.at(8));
    }
    catch(int wyjatek){
        cout<<"wykryto blad w cenie jednych z wczasow!"<<endl;
        return;
    }
    try{
        this->rodzajTransportu(opis, 9, noweWczasy);
        if (opis.size()>12){
            this->rodzajTransportu(opis, 11, noweWczasy);
            if(opis.size()==15){
                this->rodzajTransportu(opis, 13, noweWczasy);
            }
        }
    }
    catch(int wyjatek){
        if (wyjatek==1) cout<<"Zla cena ktoregos ze srodkow transportu! Te wczasy zostana pominiete!"<<endl;
        if (wyjatek==2) cout<<"Zly rodzaj transportu! Te wczasy zostana pominiete!"<<endl;
        return;
    }
    this->lista_wczasow.push_back(noweWczasy);
}

//Funkcja dodajaca objazdowke z pliku do wektora objazdowek
void BiuroPodrozy::tworzObjazdowke(vector <char*> opis){
    WycieczkaObjazdowa nowaObjazdowka;

    strcpy(nowaObjazdowka.nazwa,opis.at(1));
    try{
        for (int i=2;i<8;i++){
            if (atoi(opis.at(i))==0) throw 1;
        }
        nowaObjazdowka.data_rozpoczecia.tm_year=atoi(opis.at(2));
        nowaObjazdowka.data_rozpoczecia.tm_mon=atoi(opis.at(3));
        nowaObjazdowka.data_rozpoczecia.tm_mday=atoi(opis.at(4));
        nowaObjazdowka.data_zakonczenia.tm_year=atoi(opis.at(5));
        nowaObjazdowka.data_zakonczenia.tm_mon=atoi(opis.at(6));
        nowaObjazdowka.data_zakonczenia.tm_mday=atoi(opis.at(7));
    }
    catch (int wyjatek){
        cout<<"Zly format daty! Ta objazdowka zostaje pominieta!"<<endl;
        return;
    }
    int ilosc_danych=opis.size();

    for (int i=8; i<(ilosc_danych-1); i=i+2){
        if (atoi(opis.at(i))==0){
            string pomoc=opis.at(i);
            string pomoc2=opis.at(i+1);
            nowaObjazdowka.lista_miast.push_back(pomoc);
            nowaObjazdowka.lista_krajow.insert(pomoc2);
        }else{
            nowaObjazdowka.ostatni_kraj=opis.at(i-1);
            try{
                if (atoi(opis.at(i))==0) throw 1;
                nowaObjazdowka.kosztWycieczki=atoi(opis.at(i));
            }
            catch(int wyjatek){
                return;
            }
            try{
                this->rodzajTransportu2(opis, i+1, nowaObjazdowka);
            }
            catch(int wyjatek){
                cout<<"zly rodzaj transportu. Ta objazdowka zostaje pominieta!"<<endl;
                return;
            }
        }
    }
this->lista_objazdowek.push_back(nowaObjazdowka);
}

//dodac zabezpieczenie, jesli wystapi jakis blad to wywiesic flage
 void BiuroPodrozy::rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy){
     if (atoi(opis.at(i+1))==0) throw 1;
     string pomocniczy=opis.at(i);

        if (pomocniczy=="Autokar") {
            wczasy.koszt_autokar=atoi(opis.at(i+1));
        }else if (pomocniczy=="Samolot") {
            wczasy.koszt_samolot=atoi(opis.at(i+1));
        }else if (pomocniczy=="Wlasny") {
            wczasy.koszt_wlasny=atoi(opis.at(i+1));
        }else throw 2;
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
    }else throw 1;
}
//ZMIENIC WARUNEK!
void BiuroPodrozy::szukajWczasow(struct tm data, int dlugosc, float cena){

    for (unsigned int i=0;i<lista_wczasow.size();i++){
        if (porownajDate(lista_wczasow[i].data_rozpoczecia,data)){
                if((lista_wczasow[i].dlugosc_turnusu) <= dlugosc){
                  if (((lista_wczasow[i].kosztWycieczki)+(lista_wczasow[i].koszt_autokar)<=cena) ||
                     ((lista_wczasow[i].kosztWycieczki)+(lista_wczasow[i].koszt_samolot)<=cena) ||
                     ((lista_wczasow[i].kosztWycieczki)<=cena)){
                        this->liczbaWycieczek++;
                        this->drukujWczasy("plik.txt", lista_wczasow[i], cena);

                        int mnoznik=(dlugosc/lista_wczasow[i].dlugosc_turnusu);
                        if(mnoznik>1) {
                                if (((lista_wczasow[i].kosztWycieczki)*mnoznik+(lista_wczasow[i].koszt_autokar)<=cena) ||
                                ((lista_wczasow[i].kosztWycieczki)*mnoznik+(lista_wczasow[i].koszt_samolot)<=cena) ||
                                ((lista_wczasow[i].kosztWycieczki)*mnoznik<=cena)){
                                    this->liczbaWycieczek++;
                                    this->drukujWczasy("plik.txt",lista_wczasow[i],cena, (dlugosc/lista_wczasow[i].dlugosc_turnusu));
                                } //warunek cenowy dla wielokrotnego turnusu
                        } //sprawdzenie, czy mozna rozwazac wielokrotnosc turnusu
                     } //spelniony ktorys warunek ceny
                }//koniec warunku sprawdzajacego dlugosc turnusu
            } // koniec warunku sprawdzajacego date
    }//koniec petli sprawdzajacej wszystkie elementy wektora
}
//Funkcja zapisujaca do pliku wyjsciowego wczasy spelniajace warunki
void BiuroPodrozy::drukujWczasy(char *sciezka, Wczasy &wczasy, float cena, int mnoznik){

    float cenaSamolot = mnoznik*wczasy.kosztWycieczki + wczasy.koszt_samolot;
    float cenaAutokar = mnoznik*wczasy.kosztWycieczki + wczasy.koszt_autokar;

    ofstream plik;
    plik.open(sciezka, ios_base::app); //nadpisywanie pliku
    plik<<this->liczbaWycieczek<<". "<<
    wczasy.nazwa<<" Kraj: "<<wczasy.destynacja_kraj<<" Miejscowosc: "<<wczasy.destynacja_miasto<<" Koszt: ";

    if (cenaAutokar<=cena) plik<<cenaAutokar<<"(Autokar) ";
    if (cenaSamolot<=cena) plik<<cenaSamolot<<"(Samolot) ";
    if (mnoznik*wczasy.kosztWycieczki<=cena) plik<<mnoznik*wczasy.kosztWycieczki<<"(Dojazd wlasny) ";
    plik<<" Termin: "
    <<wczasy.data_rozpoczecia.tm_year<<"."<<wczasy.data_rozpoczecia.tm_mon<<"."
    <<wczasy.data_rozpoczecia.tm_mday<<" ("<<mnoznik*wczasy.dlugosc_turnusu<<" dni)"<<endl;
    plik.close();
}

void BiuroPodrozy::szukajObjazdowek(struct tm data, int dlugosc, float cena, char przelacznik){

    for (unsigned int i=0;i<lista_objazdowek.size();i++){
            if (porownajDate(lista_objazdowek[i].data_rozpoczecia, data)) {
               if (obliczIloscDni(lista_objazdowek[i].data_rozpoczecia,lista_objazdowek[i].data_zakonczenia)<=dlugosc){
                 if ((lista_objazdowek[i].kosztWycieczki)<=cena) {
                         switch(przelacznik){
                             case 'o': {
                                        this->liczbaWycieczek++;
                                        this->drukujObjazdowke("plik.txt",lista_objazdowek[i]);
                                        break;
                                        }
                            case 'l': {
                                        for (int j=0; j<lista_wczasow.size();j++){
                                            const char *cstr = (lista_objazdowek[i].ostatni_kraj).c_str();
                                            if (strcmp(lista_wczasow[j].destynacja_kraj, cstr)==0) this->sprawdzLaczona(lista_objazdowek[i],lista_wczasow[j],dlugosc, cena);
                                        }
                                        break;
                                        }
                         }
                 }//warunek ceny
               }//sprawdzenie warunku dlugosci objazdowki
            } //sprawdzenie daty rozpoczecia
    }
}
/*
struct tm BiuroPodrozy::dodajDate(struct tm &data, int dlugosc){

        switch (data.tm_mon){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            data=this->obliczDate(31, data, dlugosc);
            break;
        case 2:
            if ((data.tm_mon%4)==0) data=this->obliczDate(29,data,dlugosc);
            else data=this->obliczDate(28,data, dlugosc);
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            data=this->obliczDate(30,data, dlugosc);
            break;
        }

}
//tylko do 30/31 dni!
struct tm BiuroPodrozy::obliczDate(int dni,struct tm &data, int dlugosc){

        if((dni-data.tm_mday)>dlugosc){
            data.tm_mday = data.tm_mday + dlugosc;
        }else if (data.tm_mon==12){
            data.tm_year++;
            data.tm_mon=1;
            data.tm_mday=dlugosc-(dni-data.tm_mday);
        }else {
            data.tm_mon++;
            data.tm_mday = dlugosc-(dni-data.tm_mday);
        }
        return data;
}
*/
bool BiuroPodrozy::porownajDate(struct tm data1, struct tm data2){

    if((data1.tm_year)<(data2.tm_year)) return false;
    else if((data1.tm_year)>(data2.tm_year)) return true;
    else if ((data1.tm_year)<(data2.tm_year)) return false;
    else if ((data1.tm_mon)>(data2.tm_mon)) return true;
    else if ((data1.tm_mday)>=(data2.tm_mday)) return true;
    else return false;

}
//Funkcja obliczajaca ilosc dni pomiedzy dwiema datami
double BiuroPodrozy::obliczIloscDni(struct tm data1, struct tm data2){

    struct tm pomoc1, pomoc2;
    time_t rawtime;
    time ( &rawtime );
    pomoc1 = *localtime ( &rawtime );
    pomoc2 = *localtime( &rawtime);

    pomoc1.tm_year= data1.tm_year - 1900;
    pomoc1.tm_mon = data1.tm_mon - 1;
    pomoc1.tm_mday = data1.tm_mday;
    pomoc2.tm_year= data2.tm_year - 1900;
    pomoc2.tm_mon = data2.tm_mon - 1;
    pomoc2.tm_mday = data2.tm_mday;

    double sekundy = difftime(mktime(&pomoc2),mktime(&pomoc1));
    double wynik = sekundy/86400;
    return wynik;


}

void BiuroPodrozy::drukujObjazdowke(char *sciezka, WycieczkaObjazdowa &objazd){

    ofstream plik;
    plik.open(sciezka, ios_base::app); //nadpisywanie pliku

    plik<<this->liczbaWycieczek<<". "<<
    objazd.nazwa<<" Kraje: ";
    for (const string& x: objazd.lista_krajow) plik<< x<< " ";
    plik<<"Miasta: ";
    for (unsigned int i=0; i<objazd.lista_miast.size(); i++) plik<<objazd.lista_miast[i]<<" ";
    plik<<"Koszt: "<<objazd.kosztWycieczki<<" Termin: "<<
    objazd.data_rozpoczecia.tm_year<<"."<<objazd.data_rozpoczecia.tm_mon<<"."<<objazd.data_rozpoczecia.tm_mday<<" - "<<
    objazd.data_zakonczenia.tm_year<<"."<<objazd.data_zakonczenia.tm_mon<<"."<<objazd.data_zakonczenia.tm_mday<<endl;

    plik.close();

}
void BiuroPodrozy::sprawdzLaczona(WycieczkaObjazdowa &objazd, Wczasy &wczasy, int dlugosc, float cena){
    if ((dlugosc - (obliczIloscDni(objazd.data_rozpoczecia,objazd.data_zakonczenia))) >= wczasy.dlugosc_turnusu) {
        if (porownajDate(wczasy.data_rozpoczecia,objazd.data_zakonczenia)){
                if ((objazd.kosztWycieczki + wczasy.kosztWycieczki) <= cena) {
                    this->liczbaWycieczek++;
                    this->drukujLaczona("plik.txt",objazd, wczasy);
                } //warunek ceny
        } //warunek sprawdzajacy czy wczasy rozpoczynaja sie po objazdowce
    }//warunek sprawdzajacy dlugosc laczonej wycieczki
}

void BiuroPodrozy::drukujLaczona(char *sciezka, WycieczkaObjazdowa &objazd, Wczasy &wczasy){

    ofstream plik;
    plik.open(sciezka, ios_base::app); //nadpisywanie pliku

    plik<<this->liczbaWycieczek<<". "<<"Wycieczka laczona "<<
    objazd.nazwa<<" Kraje: ";
    for (const string& x: objazd.lista_krajow) plik<< x<< " ";
    plik<<"Miasta: ";
    for (unsigned int i=0; i<objazd.lista_miast.size(); i++) plik<<objazd.lista_miast[i]<<" ";
    plik<<" Termin: "<<
    objazd.data_rozpoczecia.tm_year<<"."<<objazd.data_rozpoczecia.tm_mon<<"."<<objazd.data_rozpoczecia.tm_mday<<" - "<<
    objazd.data_zakonczenia.tm_year<<"."<<objazd.data_zakonczenia.tm_mon<<"."<<objazd.data_zakonczenia.tm_mday;
    plik<<" Wczasy w "<<wczasy.destynacja_kraj<<" Miasto: "<<wczasy.destynacja_miasto<<" Termin: "<<
    wczasy.data_rozpoczecia.tm_year<<"."<<wczasy.data_rozpoczecia.tm_mon<<"."<<wczasy.data_rozpoczecia.tm_mday<<
    " ("<<wczasy.dlugosc_turnusu<<" dni)'"<<" Koszt: "<<(objazd.kosztWycieczki+wczasy.kosztWycieczki)<<endl;

    plik.close();

}
