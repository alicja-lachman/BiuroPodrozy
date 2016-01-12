#include "Wczasy.h"
#include "BiuroPodrozy.h"
#include <string.h>
#include <iostream>

Wczasy::Wczasy(string nazwa, struct tm data_rozpoczecia,int dlugosc, string destynacja_miasto, string destynacja_kraj, float kosztWycieczki, float koszt_autokar, float koszt_samolot, float koszt_wlasny):
    Wycieczka(nazwa, data_rozpoczecia, kosztWycieczki),destynacja_miasto(destynacja_miasto), destynacja_kraj(destynacja_kraj),
    dlugosc_turnusu(dlugosc), koszt_autokar(koszt_autokar), koszt_samolot(koszt_samolot),
    koszt_wlasny(koszt_wlasny){}

Wczasy::~Wczasy(){}

string Wczasy::getDestynacjaKraj(){
    return destynacja_kraj;
}

string Wczasy::getDestynacjaMiasto(){
    return destynacja_miasto;
}

int Wczasy::getDlugosc(){
    return dlugosc_turnusu;
}

void Wczasy::drukuj(BiuroPodrozy *biuro, int mnoznik){

    float cenaSamolot = mnoznik*this->getKosztWycieczki() + this->koszt_samolot;
    float cenaAutokar = mnoznik*this->getKosztWycieczki() + this->koszt_autokar;

    ofstream plik;
    plik.open(biuro->plik_wyjsciowy, ios_base::app); //nadpisywanie pliku
    plik<<biuro->getIloscWycieczek()<<". ";
    plik<<" "<<this->getNazwa()<<" Kraj: "<<this->destynacja_kraj<<" Miejscowosc: "<<this->destynacja_miasto<<" Koszt: ";

    if (cenaAutokar<=biuro->cena) plik<<cenaAutokar<<"(Autokar) ";
    if (cenaSamolot<=biuro->cena) plik<<cenaSamolot<<"(Samolot) ";
    if (mnoznik*this->getKosztWycieczki()<=biuro->cena) plik<<mnoznik*this->getKosztWycieczki()<<"(Dojazd wlasny) ";
    plik<<" Termin: "
    <<this->getDataRozp().tm_year<<"."<<this->getDataRozp().tm_mon<<"."
    <<this->getDataRozp().tm_mday<<" ("<<mnoznik*this->getDlugosc()<<" dni)"<<endl;

    plik.close();

}
//Funkcja sprawdzajaca czy dane wczasy spelniaja warunki okreslone w biurze
void Wczasy::sprawdz(BiuroPodrozy *biuro){
    Wczasy *pd;
    pd=dynamic_cast<Wczasy*>(this);

    if (pd!=NULL) {
        if (porownajDate(pd->getDataRozp(),biuro->data)){

            int mnoznik=(biuro->dlugosc/pd->dlugosc_turnusu);
            for(;mnoznik>=1;mnoznik--) {
                if (((pd->getKosztWycieczki())*mnoznik+(pd->koszt_autokar)<=biuro->cena) ||
                ((pd->getKosztWycieczki())*mnoznik+(pd->koszt_samolot)<=biuro->cena) ||
                ((pd->getKosztWycieczki())*mnoznik<=biuro->cena)){
                    biuro->zwiekszLicznikWycieczek();
                    pd->drukuj(biuro, mnoznik);
                } //warunek cenowy dla wielokrotnego turnusu
            } //sprawdzenie lacznie z wielokrotnoscia turnusow
        } // koniec warunku sprawdzajacego date
    }
}
