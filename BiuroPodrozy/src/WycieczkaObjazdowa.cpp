#include "WycieczkaObjazdowa.h"
#include <string.h>

WycieczkaObjazdowa::WycieczkaObjazdowa()
{
    strcpy(dojazd,"brak");
    data_zakonczenia.tm_mday=1;
    data_zakonczenia.tm_mon=1;
    data_zakonczenia.tm_year=1902;
    ostatni_kraj="brak";
}

WycieczkaObjazdowa::~WycieczkaObjazdowa(){}
