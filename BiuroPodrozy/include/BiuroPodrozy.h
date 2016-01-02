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
       BiuroPodrozy();
       virtual ~BiuroPodrozy();
       void czytajPlik(char *folder);
       vector <Wczasy> lista_wczasow;
       vector <WycieczkaObjazdowa> lista_objazdowek;
       void szukajWczasow(struct tm data, int dlugosc, float cena);
       void szukajObjazdowek(struct tm data, int dlugosc, float cena, char przelacznik);
       struct tm dodajDate(struct tm &data, int dlugosc);
       struct tm obliczDate(int dni,struct tm &data, int dlugosc);
       bool porownajDate(struct tm data1, struct tm data2);
       double obliczIloscDni(struct tm data1, struct tm data2);
    private:
       static void rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy);
       static void rodzajTransportu2(vector<char*>opis,int i, WycieczkaObjazdowa &objazdowka);
       void interpretujDane(string zawartosc);
       void tworzWczasy(vector <char*> opis);
       void tworzObjazdowke(vector <char*> opis);
       void drukujWczasy(char *sciezka, Wczasy &wczasy,float cena, int mnoznik=1);
       void drukujObjazdowke(char *sciezka, WycieczkaObjazdowa &objazd);
       int liczbaWycieczek;
       void sprawdzLaczona(WycieczkaObjazdowa &objazd, Wczasy &wczasy, int dlugosc, float cena);
       void drukujLaczona(char *sciezka, WycieczkaObjazdowa &objazd, Wczasy &wczasy);

};

#endif // BIUROPODROZY_H
