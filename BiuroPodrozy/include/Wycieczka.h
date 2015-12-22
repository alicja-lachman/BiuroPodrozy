#ifndef WYCIECZKA_H
#define WYCIECZKA_H
#include <time.h>

class Wycieczka
{
    public:
        Wycieczka();
        virtual ~Wycieczka();
        friend class BiuroPodrozy;
    private:
        char nazwa[30];
        struct tm data_rozpoczecia;
        int kosztWycieczki;
};

#endif // WYCIECZKA_H
