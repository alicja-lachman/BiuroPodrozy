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
        static vector <Wczasy> lista_wczasow;
        vector <WycieczkaObjazdowa> lista_objazdowek;
        BiuroPodrozy();
        virtual ~BiuroPodrozy();
        static void rodzajTransportu(vector<char*>opis,int i, Wczasy &wczasy);
       void interpretujDane(string zawartosc);
       static void tworzWczasy(vector <char*> opis);
        void czytajPlik();
    protected:
    private:
};

#endif // BIUROPODROZY_H
