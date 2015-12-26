#ifndef WYCIECZKAOBJAZDOWA_H
#define WYCIECZKAOBJAZDOWA_H
#include <vector>
#include <set>
#include <Wycieczka.h>
#include <string>

using namespace std;

class WycieczkaObjazdowa : public Wycieczka
{
private:
        char dojazd[30];
        struct tm data_zakonczenia;
        vector <string> lista_miast;
        set <string> lista_krajow;
    public:
        WycieczkaObjazdowa();
        virtual ~WycieczkaObjazdowa();
        friend class BiuroPodrozy;
};

#endif // WYCIECZKAOBJAZDOWA_H
