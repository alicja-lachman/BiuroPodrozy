#ifndef LACZONA_H
#define LACZONA_H
#include "Wczasy.h"
#include "WycieczkaObjazdowa.h"

class Laczona
{
    public:
        Laczona(Wczasy &wczasy, WycieczkaObjazdowa &objazd);
        virtual ~Laczona();
        void sprawdz(BiuroPodrozy *biuro);
    private:
        Wczasy &wczasy;
        WycieczkaObjazdowa &objazd;
        void drukujLaczona(BiuroPodrozy *biuro);
};

#endif // LACZONA_H
