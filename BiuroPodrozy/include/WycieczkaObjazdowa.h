#ifndef WYCIECZKAOBJAZDOWA_H
#define WYCIECZKAOBJAZDOWA_H
#include <vector>
#include <set>
#include <Wycieczka.h>
#include <string>

using namespace std;
class Wczasy;
class WycieczkaLaczona;

class WycieczkaObjazdowa : public Wycieczka
{
private:
        string dojazd;
        struct tm data_zakonczenia;
        vector <string> lista_miast;
        set <string> lista_krajow;
        string ostatni_kraj;
    public:
        WycieczkaObjazdowa(string nazwa1, struct tm data_rozp, float koszt_wyc, string dojazd, struct tm data_zak, vector <string> lista_m, set <string> lista_k, string ostatni_k);
        ~WycieczkaObjazdowa();
        void drukuj(BiuroPodrozy *biuro, int mnoznik=1);
        void sprawdz(BiuroPodrozy *biuro);
        struct tm getDataZak();
        string getListaMiast(int i);
        int getListaMiastRozmiar();
        set <string> getListaKrajow();
};

#endif // WYCIECZKAOBJAZDOWA_H
