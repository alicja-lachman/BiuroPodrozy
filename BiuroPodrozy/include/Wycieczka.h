#ifndef WYCIECZKA_H
#define WYCIECZKA_H
#include <time.h>
#include <string>
#include <iostream>
class BiuroPodrozy;
class Wycieczka
{
   protected:
        std::string nazwa;
        struct tm data_rozpoczecia;
        float kosztWycieczki;
    public:
        Wycieczka(std::string nazwa1, struct tm data_rozp, float koszt_wyc);
        Wycieczka();
        virtual void sprawdz(BiuroPodrozy *biuro)=0;
        virtual void drukuj(BiuroPodrozy *biuro, int mnoznik=1)=0;
        virtual ~Wycieczka();
        bool porownajDate(struct tm data1, struct tm data2);
        int obliczIloscDni(struct tm data1, struct tm data2);

};

#endif // WYCIECZKA_H
