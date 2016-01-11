#include "Wczasy.h"
#include "BiuroPodrozy.h"
#include <string.h>
#include <iostream>

Wczasy::Wczasy(string nazwa, struct tm data_rozpoczecia,int dlugosc, string destynacja_miasto, string destynacja_kraj, float kosztWycieczki, float koszt_autokar, float koszt_samolot, float koszt_wlasny):
    Wycieczka(nazwa, data_rozpoczecia, kosztWycieczki),
     destynacja_miasto(destynacja_miasto), destynacja_kraj(destynacja_kraj),
     dlugosc_turnusu(dlugosc), koszt_autokar(koszt_autokar), koszt_samolot(koszt_samolot),
      koszt_wlasny(koszt_wlasny){

      }


Wczasy::~Wczasy(){}
string Wczasy::zwrocDestynacje(){
    return destynacja_kraj;
}
void Wczasy::drukuj(BiuroPodrozy *biuro, int mnoznik){

    float cenaSamolot = mnoznik*this->kosztWycieczki + this->koszt_samolot;
    float cenaAutokar = mnoznik*this->kosztWycieczki + this->koszt_autokar;
    ofstream plik;
    plik.open(biuro->plik_wyjsciowy, ios_base::app); //nadpisywanie pliku
    plik<<biuro->podajIlosc()<<". ";
    plik<<" "<<this->nazwa<<" Kraj: "<<this->destynacja_kraj<<" Miejscowosc: "<<this->destynacja_miasto<<" Koszt: ";

    if (cenaAutokar<=biuro->cena) plik<<cenaAutokar<<"(Autokar) ";
    if (cenaSamolot<=biuro->cena) plik<<cenaSamolot<<"(Samolot) ";
    if (mnoznik*this->kosztWycieczki<=biuro->cena) plik<<mnoznik*this->kosztWycieczki<<"(Dojazd wlasny) ";
    plik<<" Termin: "
    <<this->data_rozpoczecia.tm_year<<"."<<this->data_rozpoczecia.tm_mon<<"."
    <<this->data_rozpoczecia.tm_mday<<" ("<<mnoznik*this->dlugosc_turnusu<<" dni)"<<endl;

    plik.close();

}
void Wczasy::sprawdz(BiuroPodrozy *biuro){
    Wczasy *pd;
    pd=dynamic_cast<Wczasy*>(this);
    if (pd!=NULL) {
        if (porownajDate(pd->data_rozpoczecia,biuro->data)){

            int mnoznik=(biuro->dlugosc/pd->dlugosc_turnusu);
            for(;mnoznik>=1;mnoznik--) {
                if (((pd->kosztWycieczki)*mnoznik+(pd->koszt_autokar)<=biuro->cena) ||
                ((pd->kosztWycieczki)*mnoznik+(pd->koszt_samolot)<=biuro->cena) ||
                ((pd->kosztWycieczki)*mnoznik<=biuro->cena)){
                    biuro->zwiekszLicznik();
                    pd->drukuj(biuro, mnoznik);
                } //warunek cenowy dla wielokrotnego turnusu
            } //sprawdzenie lacznie z wielokrotnoscia turnusow
        } // koniec warunku sprawdzajacego date
    }
}
