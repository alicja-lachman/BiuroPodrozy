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
        string destynacja_miasto;
        string destynacja_kraj;
        int dlugosc_turnusu;
        float koszt_autokar;
        float koszt_samolot;
        float koszt_wlasny;
public:
        Wczasy(string nazwa, struct tm data_rozpoczecia,int dlugosc, string destynacja_miasto, string destynacja_kraj, float kosztWycieczki, float koszt_autokar, float koszt_samolot, float koszt_wlasny);
        ~Wczasy();
        void sprawdz(BiuroPodrozy *biuro);
        void drukuj(BiuroPodrozy *biuro, int mnoznik=1);
        string getDestynacjaKraj();
        string getDestynacjaMiasto();
        struct tm getDataZak();
        int getDlugosc();
};

#endif // WCZASY_H
