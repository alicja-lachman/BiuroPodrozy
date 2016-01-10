#include "BiuroPodrozy.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <stdlib.h>
using namespace std;

BiuroPodrozy::BiuroPodrozy(char *sciezka, char *plik_wyjsciowy, char *rodzaj, int dlugosc, float cena, struct tm data)
{
    this->liczbaWycieczek=0;
    this->sciezka=sciezka;
    this->plik_wyjsciowy=plik_wyjsciowy;
    this->rodzaj=rodzaj;
    this->dlugosc=dlugosc;
    this->cena=cena;
    this->data=data;
}

BiuroPodrozy::~BiuroPodrozy(){
    this->liczbaWycieczek=0;
}

int BiuroPodrozy::podajIlosc(){
    return liczbaWycieczek;
}
//Funkcja sprawdzajaca, czy dany plik opisuje wycieczke objazdowa czy wczasy
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
            //this->tworzWczasy(dane);
            wskaznik_wczasy=this->tworzWczasy(dane);
            lista_wycieczek.push_back(wskaznik_wczasy);
            cout<<wskaznik_wczasy->nazwa<<endl;
    }
   // else if (pomocniczy=="WO:") this->tworzObjazdowke(dane);
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
    cout<<lista_wycieczek[1]->nazwa<<endl;
}

//Funkcja tworzaca nowe wczasy i dodajace je do wektora wczasow
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
    //Wczasy noweWczasy;
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
        //return 0;
    }
    destynacja_miasto.assign(opis.at(6));
    destynacja_kraj.assign(opis.at(7));
    try{
        if (atoi(opis.at(8))==0) throw 1;
        koszt_wycieczki=atoi(opis.at(8));
        cout<<"koszt"<<koszt_wycieczki<<endl;
    }
    catch(int wyjatek){
        cout<<"wykryto blad w cenie jednych z wczasow!"<<endl;
        //return;
    }
    try{
        for(int i=9; i<opis.size(); i=i+2){
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
        //return;
    }
   wskaznik_wczasy=new Wczasy(nazwa, data_rozp, dlugosc, destynacja_miasto, destynacja_kraj, koszt_wycieczki, koszt_autokar, koszt_samolot, koszt_wlasny);
   return wskaznik_wczasy;
}
/*
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
                nowaObjazdowka.kosztWycieczki=atof(opis.at(i));
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
*/
//dodac zabezpieczenie, jesli wystapi jakis blad to wywiesic flage
 void BiuroPodrozy::rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy){
     if (atoi(opis.at(i+1))==0) throw 1;
     string pomocniczy=opis.at(i);

        if (pomocniczy=="Autokar") {
            wczasy.koszt_autokar=atof(opis.at(i+1));
        }else if (pomocniczy=="Samolot") {
            wczasy.koszt_samolot=atof(opis.at(i+1));
        }else if (pomocniczy=="Wlasny") {
            wczasy.koszt_wlasny=atof(opis.at(i+1));
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
/*
void BiuroPodrozy::szukajWczasow(struct tm data, int dlugosc, float cena, char *plik){

    for (unsigned int i=0;i<lista_wczasow.size();i++){
        if (porownajDate(lista_wczasow[i].data_rozpoczecia,data)){
                        int mnoznik=(dlugosc/lista_wczasow[i].dlugosc_turnusu);
                        for(;mnoznik>=1;mnoznik--) {
                                if (((lista_wczasow[i].kosztWycieczki)*mnoznik+(lista_wczasow[i].koszt_autokar)<=cena) ||
                                ((lista_wczasow[i].kosztWycieczki)*mnoznik+(lista_wczasow[i].koszt_samolot)<=cena) ||
                                ((lista_wczasow[i].kosztWycieczki)*mnoznik<=cena)){
                                    this->liczbaWycieczek++;
                                    this->drukujWczasy(plik,lista_wczasow[i],cena, mnoznik);
                                } //warunek cenowy dla wielokrotnego turnusu
                        } //sprawdzenie lacznie z wielokrotnoscia turnusow
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

void BiuroPodrozy::szukajObjazdowek(struct tm data, int dlugosc, float cena, char *plik, char przelacznik){

    for (unsigned int i=0;i<lista_objazdowek.size();i++){
            if (porownajDate(lista_objazdowek[i].data_rozpoczecia, data)) {
               if (obliczIloscDni(lista_objazdowek[i].data_rozpoczecia,lista_objazdowek[i].data_zakonczenia)<=dlugosc){
                 if ((lista_objazdowek[i].kosztWycieczki)<=cena) {
                         switch(przelacznik){
                             case 'o': {
                                        this->liczbaWycieczek++;
                                        this->drukujObjazdowke(plik,lista_objazdowek[i]);
                                        break;
                                        }
                            case 'l': {
                                        for (unsigned int j=0; j<lista_wczasow.size();j++){
                                            const char *cstr = (lista_objazdowek[i].ostatni_kraj).c_str();
                                            if (strcmp(lista_wczasow[j].destynacja_kraj, cstr)==0) this->sprawdzLaczona(lista_objazdowek[i],lista_wczasow[j],dlugosc, cena, plik);
                                        }
                                        break;
                                        }
                         }
                 }//warunek ceny
               }//sprawdzenie warunku dlugosci objazdowki
            } //sprawdzenie daty rozpoczecia
    }
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
int BiuroPodrozy::obliczIloscDni(struct tm data1, struct tm data2){

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
    int wynik = sekundy/86400;
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
void BiuroPodrozy::sprawdzLaczona(WycieczkaObjazdowa &objazd, Wczasy &wczasy, int dlugosc, float cena, char *plik){
    if ((dlugosc - (obliczIloscDni(objazd.data_rozpoczecia,objazd.data_zakonczenia))) >= wczasy.dlugosc_turnusu) {
        if (porownajDate(wczasy.data_rozpoczecia,objazd.data_zakonczenia)){
                if ((objazd.kosztWycieczki + wczasy.kosztWycieczki) <= cena) {
                    this->liczbaWycieczek++;
                    this->drukujLaczona(plik,objazd, wczasy);
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
    " ("<<wczasy.dlugosc_turnusu<<" dni)"<<" Koszt: "<<(objazd.kosztWycieczki+wczasy.kosztWycieczki)<<endl;

    plik.close();

}
