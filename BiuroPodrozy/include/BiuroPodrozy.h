#ifndef BIUROPODROZY_H
#define BIUROPODROZY_H

#include "WycieczkaObjazdowa.h"
#include <string.h>
#include <fstream>
#include <vector>
class Wczasy;
using namespace std;
class BiuroPodrozy
{
    public:
       BiuroPodrozy(char *sciezka, char *plik_wyjsciowy, char *rodzaj, int dlugosc, float cena, struct tm data, int liczbaWycieczek=0);
       ~BiuroPodrozy();
       void czytajPliki();

       int podajIlosc();
       void szukajWycieczek();
       char *sciezka;
        char *plik_wyjsciowy;
        char *rodzaj;
        int dlugosc;
        float cena;
        struct tm data;
        void zwiekszLicznik();
        vector <Wycieczka*> lista_wycieczek;
    private:
         void szukajWczasow();
       void szukajObjazdowek();

       void interpretujDane(string zawartosc);
       Wczasy* tworzWczasy(vector <char*> opis);
       WycieczkaObjazdowa* tworzObjazdowke(vector <char*> opis);

       void drukujWczasy(char *sciezka, Wczasy &wczasy,float cena, int mnoznik=1);
       void drukujObjazdowke(char *sciezka, WycieczkaObjazdowa &objazd);
       int liczbaWycieczek;
       void sprawdzLaczona(WycieczkaObjazdowa &objazd, Wczasy &wczasy, int dlugosc, float cena, char *plik);
       void drukujLaczona(char *sciezka, WycieczkaObjazdowa &objazd, Wczasy &wczasy);
       bool porownajDate(struct tm data1, struct tm data2);
       int obliczIloscDni(struct tm data1, struct tm data2);
};

#endif // BIUROPODROZY_H
