#ifndef WCZASY_H
#define WCZASY_H
#include <Wycieczka.h>
#include <vector>
using namespace std;

class Wczasy : public Wycieczka
{
private:
        float koszt_autokar;
        float koszt_samolot;
        float koszt_wlasny;
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
