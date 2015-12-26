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
        }else{
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

    for (int i=8; i<(ilosc_danych-1); i=i+2){

        if (atoi(opis.at(i))==0){
            string pomoc=opis.at(i);
            string pomoc2=opis.at(i+1);
            nowaObjazdowka.lista_miast.push_back(pomoc);
            nowaObjazdowka.lista_krajow.insert(pomoc2);


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
        wczasy.koszt_autokar=atoi(opis.at(i+1));
     }else if (pomocniczy=="Samolot") {
        wczasy.koszt_samolot=atoi(opis.at(i+1));
     }else if (pomocniczy=="Wlasny") {
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
            if (((lista_wczasow[i].data_rozpoczecia.tm_mon) > data.tm_mon)     //Bardzo dlugi warunek dla miesiaca
            || ((lista_wczasow[i].data_rozpoczecia.tm_mon) == data.tm_mon
            && (lista_wczasow[i].data_rozpoczecia.tm_mday) >= data.tm_mday)){
                cout<<"yay";
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
            } //koniec warunku sprawdzajacego miesiac (bardzo długi warunek)
        } //koniec warunku sprawdzajacego rok
    }//koniec petli sprawdzajacej wszystkie lementy wektora
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

void BiuroPodrozy::szukajObjazdowek(struct tm data, int dlugosc, float cena){

    for (unsigned int i=0;i<lista_objazdowek.size();i++){
            if (porownajDate(lista_objazdowek[i].data_rozpoczecia, data)) {
               if (obliczIloscDni(lista_objazdowek[i].data_zakonczenia, lista_objazdowek[i].data_rozpoczecia)<=dlugosc){
                 if ((lista_objazdowek[i].kosztWycieczki)<=cena) {
                         this->liczbaWycieczek++;
                         this->drukujObjazdowke("plik.txt",lista_objazdowek[i]);
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
   for (unsigned int i=0; i<objazd.lista_miast.size(); i++){
       plik<<objazd.lista_miast[i]<<" ";
    }

   //plik<<objazd.kosztWycieczki<<endl;
    plik.close();

}
