#ifndef WYCIECZKA_H
#define WYCIECZKA_H
#include <time.h>

class Wycieczka
{
    public:
        struct tm data_rozpoczecia;
        enum dojazd {autokar, samolot, wlasny};
        int koszt_autokar;
        int koszt_samolot;
        int koszt_wlasny;
        Wycieczka();
        virtual ~Wycieczka();
        virtual void tworzObiekt();


    protected:
    private:
};

#endif // WYCIECZKA_H
