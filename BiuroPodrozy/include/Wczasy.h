#ifndef WCZASY_H
#define WCZASY_H
#include "BiuroPodrozy.h"
#include "Wycieczka.h"
#include <vector>
using namespace std;
class BiuroPodrozy;
class Wczasy : public Wycieczka
{
private:
        float koszt_autokar;
        float koszt_samolot;
        float koszt_wlasny;
        int dlugosc_turnusu;
        string destynacja_kraj;
        string destynacja_miasto;

   // protected:
public:
        Wczasy(string nazwa, struct tm data_rozpoczecia,int dlugosc, string destynacja_miasto, string destynacja_kraj, float kosztWycieczki, float koszt_autokar, float koszt_samolot, float koszt_wlasny);
        void sprawdz(BiuroPodrozy *biuro);
        void drukuj(BiuroPodrozy *biuro, int mnoznik=1);
        string zwrocDestynacje();
        ~Wczasy();


};

#endif // WCZASY_H
