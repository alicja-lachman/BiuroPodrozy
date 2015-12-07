#ifndef WYCIECZKA_H
#define WYCIECZKA_H
#include <time.h>

class Wycieczka
{
    public:
        char nazwa[30];
        struct tm data_rozpoczecia;
        char dojazd[30];        //problemy z enumem
        int kosztWycieczki;
        Wycieczka();
        virtual ~Wycieczka();
        virtual void tworzObiekt();


    protected:
    private:
};

#endif // WYCIECZKA_H
