#ifndef WCZASY_H
#define WCZASY_H
#include <Wycieczka.h>

using namespace std;

class Wczasy : public Wycieczka
{
    public:
        int dlugosc_turnusu;
        char destynacja[40];
        Wczasy();
        virtual ~Wczasy();
    protected:
    private:
};

#endif // WCZASY_H
