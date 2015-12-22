#ifndef WCZASY_H
#define WCZASY_H
#include <Wycieczka.h>
#include <vector>
using namespace std;

class Wczasy : public Wycieczka
{
private:
        int koszt_autokar;
        int koszt_samolot;
        int koszt_wlasny;
        int dlugosc_turnusu;
        char destynacja_kraj[30];
        char destynacja_miasto[30];
    protected:
    public:
        Wczasy();
        virtual ~Wczasy();
        friend class BiuroPodrozy;
};

#endif // WCZASY_H
