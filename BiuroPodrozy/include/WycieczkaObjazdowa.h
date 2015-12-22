#ifndef WYCIECZKAOBJAZDOWA_H
#define WYCIECZKAOBJAZDOWA_H
#include <list>
#include <Wycieczka.h>
#include <string>

using namespace std;

class WycieczkaObjazdowa : public Wycieczka
{
private:
        char dojazd[30];
        struct tm data_zakonczenia;
        list <string> lista_miast;
        list <string> lista_krajow;
    public:
        WycieczkaObjazdowa();
        virtual ~WycieczkaObjazdowa();
        friend class BiuroPodrozy;
};

#endif // WYCIECZKAOBJAZDOWA_H
