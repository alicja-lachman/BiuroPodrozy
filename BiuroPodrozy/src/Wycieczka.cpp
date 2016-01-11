#include "Wycieczka.h"
#include <string.h>
#include <iostream>
using namespace std;

Wycieczka::Wycieczka(std::string nazwa1, struct tm data_rozp, float koszt_wyc){
    nazwa=nazwa1;
    data_rozpoczecia.tm_mday=data_rozp.tm_mday;
    data_rozpoczecia.tm_mon=data_rozp.tm_mon;
    data_rozpoczecia.tm_year=data_rozp.tm_year;
    kosztWycieczki=koszt_wyc;
}

Wycieczka::Wycieczka()
{
    nazwa.assign("probna");
    data_rozpoczecia.tm_mday=1;
    data_rozpoczecia.tm_mon=1;
    data_rozpoczecia.tm_year=1902;
    kosztWycieczki=0;
}
void Wycieczka::drukuj(BiuroPodrozy *biuro, int mnoznik){}

void Wycieczka::sprawdz(BiuroPodrozy *biuro){}
Wycieczka::~Wycieczka(){}

bool Wycieczka::porownajDate(struct tm data1, struct tm data2){

    if((data1.tm_year)<(data2.tm_year)) return false;
    else if((data1.tm_year)>(data2.tm_year)) return true;
    else if ((data1.tm_year)<(data2.tm_year)) return false;
    else if ((data1.tm_mon)>(data2.tm_mon)) return true;
    else if ((data1.tm_mday)>=(data2.tm_mday)) return true;
    else return false;

}
//Funkcja obliczajaca ilosc dni pomiedzy dwiema datami
int Wycieczka::obliczIloscDni(struct tm data1, struct tm data2){

    struct tm pomoc1, pomoc2;
    time_t rawtime;
    time ( &rawtime );
    pomoc1 = *localtime ( &rawtime );
    pomoc2 = *localtime( &rawtime);

    pomoc1.tm_year= data1.tm_year - 1900;
    pomoc1.tm_mon = data1.tm_mon - 1;
    pomoc1.tm_mday = data1.tm_mday;
    pomoc2.tm_year= data2.tm_year - 1900;
    pomoc2.tm_mon = data2.tm_mon - 1;
    pomoc2.tm_mday = data2.tm_mday;

    double sekundy = difftime(mktime(&pomoc2),mktime(&pomoc1));
    int wynik = sekundy/86400;
    return wynik;


}
