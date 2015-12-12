#ifndef WYCIECZKAOBJAZDOWA_H
#define WYCIECZKAOBJAZDOWA_H
#include <list>
#include <Wycieczka.h>
#include <string>

using namespace std;

class WycieczkaObjazdowa : public Wycieczka
{
    public:

        struct tm data_zakonczenia;
        list <string> lista_miast;
        list <string> lista_krajow;
        WycieczkaObjazdowa();
        virtual ~WycieczkaObjazdowa();
    protected:
    private:
};

#endif // WYCIECZKAOBJAZDOWA_H
