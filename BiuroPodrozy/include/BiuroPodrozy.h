#ifndef BIUROPODROZY_H
#define BIUROPODROZY_H
#include "Wczasy.h"
#include "WycieczkaObjazdowa.h"
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;
class BiuroPodrozy
{
    public:
       BiuroPodrozy(char *sciezka, char *plik_wyjsciowy, char *rodzaj, int dlugosc, float cena, struct tm data);
       ~BiuroPodrozy();
       void czytajPliki();
       void szukajWczasow(struct tm data, int dlugosc, float cena, char *plik);
       void szukajObjazdowek(struct tm data, int dlugosc, float cena, char *plik, char przelacznik);
       int podajIlosc();
    private:
        char *sciezka;
        char *plik_wyjsciowy;
        char *rodzaj;
        int dlugosc;
        float cena;
        struct tm data;
       vector <Wycieczka*> lista_wycieczek;
       void rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy);
       void rodzajTransportu2(vector<char*>opis,int i, WycieczkaObjazdowa &objazdowka);
       void interpretujDane(string zawartosc);
       Wczasy* tworzWczasy(vector <char*> opis);
       void tworzObjazdowke(vector <char*> opis);
       void drukujWczasy(char *sciezka, Wczasy &wczasy,float cena, int mnoznik=1);
       void drukujObjazdowke(char *sciezka, WycieczkaObjazdowa &objazd);
       int liczbaWycieczek;
       void sprawdzLaczona(WycieczkaObjazdowa &objazd, Wczasy &wczasy, int dlugosc, float cena, char *plik);
       void drukujLaczona(char *sciezka, WycieczkaObjazdowa &objazd, Wczasy &wczasy);
       bool porownajDate(struct tm data1, struct tm data2);
       int obliczIloscDni(struct tm data1, struct tm data2);
};

#endif // BIUROPODROZY_H
