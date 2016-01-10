#ifndef WCZASY_H
#define WCZASY_H
#include <Wycieczka.h>
#include <vector>
using namespace std;

class Wczasy : public Wycieczka
{
//private:
public:
        float koszt_autokar;
        float koszt_samolot;
        float koszt_wlasny;
        int dlugosc_turnusu;
        string destynacja_kraj;
        string destynacja_miasto;
        Wczasy(string nazwa, struct tm data_rozpoczecia,int dlugosc, string destynacja_miasto, string destynacja_kraj, float kosztWycieczki, float koszt_autokar, float koszt_samolot, float koszt_wlasny);
   // protected:
  //  public:
        virtual ~Wczasy();
        friend class BiuroPodrozy;
};

#endif // WCZASY_H
