#include "WycieczkaObjazdowa.h"
#include "BiuroPodrozy.h"
#include "Wczasy.h"
#include "Laczona.h"
#include <string.h>

WycieczkaObjazdowa::WycieczkaObjazdowa(string nazwa1, struct tm data_rozp, float koszt_wyc, string dojazd, struct tm data_zak, vector <string> lista_m, set <string> lista_k, string ostatni_k):
    Wycieczka(nazwa1,data_rozp, koszt_wyc),dojazd(dojazd),data_zakonczenia(data_zak),lista_miast(lista_m),lista_krajow(lista_k),ostatni_kraj(ostatni_k){}


WycieczkaObjazdowa::~WycieczkaObjazdowa(){}

struct tm WycieczkaObjazdowa::getDataZak(){
    return data_zakonczenia;
}
string WycieczkaObjazdowa::getListaMiast(int i){
    return lista_miast[i];
}
int WycieczkaObjazdowa::getListaMiastRozmiar(){
    return lista_miast.size();
}
set <string> WycieczkaObjazdowa::getListaKrajow(){
    return lista_krajow;
}
void WycieczkaObjazdowa::drukuj(BiuroPodrozy *biuro, int mnoznik){

    ofstream plik;
    plik.open(biuro->plik_wyjsciowy, ios_base::app); //nadpisywanie pliku

    plik<<biuro->podajIlosc()<<". "<<
    this->getNazwa()<<" Kraje: ";
    for (const string& x: this->lista_krajow) plik<< x<< " ";
    plik<<"Miasta: ";
    for (unsigned int i=0; i<this->lista_miast.size(); i++) plik<<this->lista_miast[i]<<" ";
    plik<<"Koszt: "<<this->getKosztWycieczki()<<" Termin: "<<
    this->getDataRozp().tm_year<<"."<<this->getDataRozp().tm_mon<<"."<<this->getDataRozp().tm_mday<<" - "<<
    this->getDataZak().tm_year<<"."<<this->getDataZak().tm_mon<<"."<<this->getDataZak().tm_mday<<endl;

    plik.close();

}
void WycieczkaObjazdowa::sprawdz(BiuroPodrozy *biuro){
    WycieczkaObjazdowa *pd;
    pd=dynamic_cast<WycieczkaObjazdowa*>(this);
    if (pd!=NULL) {
        if (porownajDate(pd->getDataRozp(), biuro->data)) {
               if (obliczIloscDni(pd->getDataRozp(),pd->getDataZak())<=biuro->dlugosc){
                    if ((pd->getKosztWycieczki())<=biuro->cena) {
                        if (strcmp(biuro->rodzaj,"o")==0 || strcmp(biuro->rodzaj,"d")==0) {
                                biuro->zwiekszLicznik();
                                pd->drukuj(biuro);
                                }
                        if ((strcmp(biuro->rodzaj,"l")==0) || (strcmp(biuro->rodzaj,"d")==0) ){
                            for (unsigned int j=0; j<biuro->lista_wycieczek.size();j++){

                                            Wczasy *wsk;
                                            wsk=dynamic_cast<Wczasy*>(biuro->lista_wycieczek[j]);

                                            if(wsk!=NULL){
                                               if ((wsk->getDestynacjaKraj())==(this->ostatni_kraj)){
                                                Laczona laczona=Laczona(*wsk,*this);
                                                laczona.sprawdz(biuro);
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
