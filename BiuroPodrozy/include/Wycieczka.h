#ifndef WYCIECZKA_H
#define WYCIECZKA_H
#include <time.h>
#include <string>
#include <iostream>

class Wycieczka
{
    private:
        std::string nazwa;
        struct tm data_rozpoczecia;
        float kosztWycieczki;
    public:
        Wycieczka(std::string nazwa1, struct tm data_rozp, float koszt_wyc);
        //Wycieczka();

        virtual ~Wycieczka();
        friend class BiuroPodrozy;
};

#endif // WYCIECZKA_H
