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
       int getIloscWycieczek();
       void szukajWycieczek();
       char *sciezka;
       char *plik_wyjsciowy;
       char *rodzaj;
       int dlugosc;
       float cena;
       struct tm data;
       void zwiekszLicznikWycieczek();
       vector <Wycieczka*> lista_wycieczek;
    private:
       void szukajWczasow();
       void szukajObjazdowek();
       void interpretujDane(string zawartosc);
       Wczasy* tworzWczasy(vector <char*> opis);
       WycieczkaObjazdowa* tworzObjazdowke(vector <char*> opis);
       int liczbaWycieczek;
};

#endif // BIUROPODROZY_H
