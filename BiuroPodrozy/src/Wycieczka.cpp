#include "Wycieczka.h"
#include <string.h>


Wycieczka::Wycieczka()
{
    strcpy(this->nazwa,"probna");
    data_rozpoczecia.tm_mday=1;
    data_rozpoczecia.tm_mon=1;
    data_rozpoczecia.tm_year=1902;
    kosztWycieczki=0;
}

Wycieczka::~Wycieczka()
{

}

