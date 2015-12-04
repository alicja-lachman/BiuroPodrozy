#ifndef WYCIECZKAOBJAZDOWA_H
#define WYCIECZKAOBJAZDOWA_H

#include <Wycieczka.h>


class WycieczkaObjazdowa : public Wycieczka
{
    public:
        char nazwa[30];
        WycieczkaObjazdowa();
        virtual ~WycieczkaObjazdowa();
    protected:
    private:
};

#endif // WYCIECZKAOBJAZDOWA_H
