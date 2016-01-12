#ifndef LACZONA_H
#define LACZONA_H
#include "Wczasy.h"
#include "WycieczkaObjazdowa.h"

class Laczona
{
    public:
        Laczona(Wczasy &wczasy, WycieczkaObjazdowa &objazd);
        virtual ~Laczona();
        Wczasy &wczasy;
        WycieczkaObjazdowa &objazd;
        void sprawdz(BiuroPodrozy *biuro);
    protected:
    private:
        void drukujLaczona(BiuroPodrozy *biuro);

};

#endif // LACZONA_H
