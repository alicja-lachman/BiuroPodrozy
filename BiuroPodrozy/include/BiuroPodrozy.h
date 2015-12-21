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
        //czo to? int podajIlosc();
        vector <Wczasy> lista_wczasow;
        vector <WycieczkaObjazdowa> lista_objazdowek;
        BiuroPodrozy();
        virtual ~BiuroPodrozy();
        static void rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy);
         static void rodzajTransportu2(vector<char*>opis,int i, WycieczkaObjazdowa &objazdowka);
       void interpretujDane(string zawartosc);
       void tworzWczasy(vector <char*> opis);
       void tworzObjazdowke(vector <char*> opis);
       void czytajPlik(char *folder);
       void szukajWczasow(struct tm data, int dlugosc, float cena);
       void drukujWczasy(char *sciezka, Wczasy &wczasy,float cena, int mnoznik=1);
       int liczbaWczasow;
    protected:

    private:

};

#endif // BIUROPODROZY_H
