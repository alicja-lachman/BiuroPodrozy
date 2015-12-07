#ifndef WCZASY_H
#define WCZASY_H
#include <Wycieczka.h>
#include <vector>
using namespace std;

class Wczasy : public Wycieczka
{
    public:
        int koszt_autokar;
        int koszt_samolot;
        int koszt_wlasny;
        int dlugosc_turnusu;
        char destynacja_kraj[30];
        char destynacja_miasto[30];
        Wczasy();
        virtual ~Wczasy();
       friend void tworzWczasy(vector <char*> opis);
    protected:
    private:
};

#endif // WCZASY_H
