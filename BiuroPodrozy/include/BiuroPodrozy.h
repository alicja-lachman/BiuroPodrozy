#ifndef BIUROPODROZY_H
#define BIUROPODROZY_H
#include <string.h>
#include <fstream>

using namespace std;
class BiuroPodrozy
{
    public:
        BiuroPodrozy();
        virtual ~BiuroPodrozy();

       void interpretujDane(string zawartosc);
        void czytajPlik();
    protected:
    private:
};

#endif // BIUROPODROZY_H
