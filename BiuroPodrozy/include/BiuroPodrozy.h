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
    protected:
    private:
};

#endif // BIUROPODROZY_H
