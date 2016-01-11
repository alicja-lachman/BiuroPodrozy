#include "WycieczkaObjazdowa.h"
#include "BiuroPodrozy.h"
#include "Wczasy.h"
#include "Laczona.h"
#include <string.h>

WycieczkaObjazdowa::WycieczkaObjazdowa(string nazwa1, struct tm data_rozp, float koszt_wyc, string dojazd, struct tm data_zak, vector <string> lista_m, set <string> lista_k, string ostatni_k):
    Wycieczka(nazwa1,data_rozp, koszt_wyc),dojazd(dojazd),data_zakonczenia(data_zak),lista_miast(lista_m),lista_krajow(lista_k),ostatni_kraj(ostatni_k){}


WycieczkaObjazdowa::~WycieczkaObjazdowa(){}

void WycieczkaObjazdowa::drukuj(BiuroPodrozy *biuro, int mnoznik){

    ofstream plik;
    plik.open(biuro->plik_wyjsciowy, ios_base::app); //nadpisywanie pliku

    plik<<biuro->podajIlosc()<<". "<<
    this->nazwa<<" Kraje: ";
    for (const string& x: this->lista_krajow) plik<< x<< " ";
    plik<<"Miasta: ";
    for (unsigned int i=0; i<this->lista_miast.size(); i++) plik<<this->lista_miast[i]<<" ";
    plik<<"Koszt: "<<this->kosztWycieczki<<" Termin: "<<
    this->data_rozpoczecia.tm_year<<"."<<this->data_rozpoczecia.tm_mon<<"."<<this->data_rozpoczecia.tm_mday<<" - "<<
    this->data_zakonczenia.tm_year<<"."<<this->data_zakonczenia.tm_mon<<"."<<this->data_zakonczenia.tm_mday<<endl;

    plik.close();

}
void WycieczkaObjazdowa::sprawdz(BiuroPodrozy *biuro){
    WycieczkaObjazdowa *pd;
    pd=dynamic_cast<WycieczkaObjazdowa*>(this);
    if (pd!=NULL) {
        if (porownajDate(pd->data_rozpoczecia, biuro->data)) {
               if (obliczIloscDni(pd->data_rozpoczecia,pd->data_zakonczenia)<=biuro->dlugosc){
                    if ((pd->kosztWycieczki)<=biuro->cena) {
                        if (strcmp(biuro->rodzaj,"o")==0 || strcmp(biuro->rodzaj,"d")==0) {
                                biuro->zwiekszLicznik();
                                pd->drukuj(biuro);
                                }
                        if ((strcmp(biuro->rodzaj,"l")==0) || (strcmp(biuro->rodzaj,"d")==0) ){
                            for (unsigned int j=0; j<biuro->lista_wycieczek.size();j++){

                                            Wczasy *wsk;
                                            wsk=dynamic_cast<Wczasy*>(biuro->lista_wycieczek[j]);

                                            if(wsk!=NULL){
                                               if ((wsk->zwrocDestynacje())==(this->ostatni_kraj)){
                                                Laczona laczona=Laczona(wsk,this);
                                                cout<<laczona.wczasy->zwrocDestynacje();
                                               } //cout<<"mozna"<<endl;
                                            //if (strcmp(wsk->destynacja_kraj, cstr)==0) cout <<"mozna laczyc chyba"<<endl;
                                                //this->sprawdzLaczona(lista_objazdowek[i],lista_wczasow[j],dlugosc, cena, plik);
                                          }
                        }
                            /*case 'l': {

                                        }
                                        break;
                                        }*/
                    }//warunek ceny
               }//sprawdzenie warunku dlugosci objazdowki
        } //sprawdzenie daty rozpoczecia
    } //warunek ze to objazdowka
//costam
}
}
