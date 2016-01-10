#include "Wczasy.h"
#include <string.h>
#include <iostream>
Wczasy::Wczasy(string nazwa, struct tm data_rozpoczecia,int dlugosc, string destynacja_miasto, string destynacja_kraj, float kosztWycieczki, float koszt_autokar, float koszt_samolot, float koszt_wlasny):
    Wycieczka(nazwa, data_rozpoczecia, kosztWycieczki), destynacja_miasto(destynacja_miasto), destynacja_kraj(destynacja_kraj), dlugosc_turnusu(dlugosc), koszt_autokar(koszt_autokar), koszt_samolot(koszt_samolot), koszt_wlasny(koszt_wlasny){}
/*
{
        cout<<"Tworze wczasy "<<endl;
        Wycieczka(nazwa, data_rozpoczecia, kosztWycieczki);
        dlugosc_turnusu=dlugosc;
        destynacja_miasto=destynacja_miasto;
        destynacja_kraj=destynacja_kraj;
        koszt_autokar=koszt_autokar;
        koszt_samolot=koszt_samolot;
        koszt_wlasny=koszt_wlasny;
}
*/
Wczasy::~Wczasy()
{

}
