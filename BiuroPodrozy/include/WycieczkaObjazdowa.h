#ifndef WYCIECZKAOBJAZDOWA_H
#define WYCIECZKAOBJAZDOWA_H
#include <list>
#include <Wycieczka.h>

using namespace std;

class WycieczkaObjazdowa : public Wycieczka
{
    public:
        char nazwa[30];
        struct tm data_zakonczenia;
        list <char> lista_miast;
        WycieczkaObjazdowa();
        virtual ~WycieczkaObjazdowa();
    protected:
    private:
};

#endif // WYCIECZKAOBJAZDOWA_H
