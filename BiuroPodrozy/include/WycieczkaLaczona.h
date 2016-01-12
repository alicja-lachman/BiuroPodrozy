#ifndef WYCIECZKALACZONA_H
#define WYCIECZKALACZONA_H


#include "Wczasy.h"
#include "WycieczkaObjazdowa.h"

class WycieczkaLaczona
{
    public:
        WycieczkaLaczona(Wczasy &wczasy, WycieczkaObjazdowa &objazd);
        virtual ~WycieczkaLaczona();
        void sprawdz(BiuroPodrozy *biuro);
    private:
        Wczasy &wczasy;
        WycieczkaObjazdowa &objazd;
        void drukujLaczona(BiuroPodrozy *biuro);
};

#endif // WYCIECZKALACZONA_H
