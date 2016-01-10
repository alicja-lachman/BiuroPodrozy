#include "Wycieczka.h"
#include <string.h>
#include <iostream>
Wycieczka::Wycieczka(std::string nazwa1, struct tm data_rozp, float koszt_wyc){
    std::cout<<"tworze wycieczke! "<<std::endl;
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


Wycieczka::~Wycieczka()
{

}

