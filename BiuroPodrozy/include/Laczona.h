#ifndef LACZONA_H
#define LACZONA_H
#include "Wczasy.h"
#include "WycieczkaObjazdowa.h"

class Laczona
{
    public:
        Laczona(Wczasy *wczasy, WycieczkaObjazdowa *objazd);
        virtual ~Laczona();
        Wczasy *wczasy;
        WycieczkaObjazdowa *objazd;
    protected:
    private:

};

#endif // LACZONA_H
