#include "Laczona.h"

Laczona::Laczona(Wczasy &wczasy, WycieczkaObjazdowa &objazd):wczasy(wczasy),objazd(objazd){}

Laczona::~Laczona(){}

void Laczona::sprawdz(BiuroPodrozy *biuro){

    if ((biuro->dlugosc - (objazd.obliczIloscDni(objazd.getDataRozp(),objazd.getDataZak()))) >= wczasy.getDlugosc()){
        if (wczasy.porownajDate(wczasy.getDataRozp(),objazd.getDataZak())){
                if ((objazd.getKosztWycieczki() + wczasy.getKosztWycieczki()) <= biuro->cena) {
                    biuro->zwiekszLicznikWycieczek();
                    this->drukujLaczona(biuro);
                } //warunek cenye
        } //warunek sprawdzajacy czy wczasy rozpoczynaja sie po objazdowce
    }//warunek sprawdzajacy dlugosc laczonej wycieczki
}

void Laczona::drukujLaczona(BiuroPodrozy *biuro){

    ofstream plik;
    plik.open(biuro->plik_wyjsciowy, ios_base::app); //nadpisywanie pliku

    plik<<biuro->getIloscWycieczek()<<". "<<"Wycieczka laczona "<<
    objazd.getNazwa()<<" + "<<wczasy.getNazwa()<<" "<<" Kraje: ";
    for (const string& x: objazd.getListaKrajow()) plik<< x<< " ";
    plik<<"Miasta: ";
    for (int i=0; i<objazd.getListaMiastRozmiar(); i++) plik<<objazd.getListaMiast(i)<<" ";
    plik<<" Termin: "<<
    objazd.getDataRozp().tm_year<<"."<<objazd.getDataRozp().tm_mon<<"."<<objazd.getDataRozp().tm_mday<<" - "<<
    objazd.getDataZak().tm_year<<"."<<objazd.getDataZak().tm_mon<<"."<<objazd.getDataZak().tm_mday;
    plik<<" Wczasy w "<<wczasy.getDestynacjaKraj()<<" Miasto: "<<wczasy.getDestynacjaMiasto()<<" Termin: "<<
    wczasy.getDataRozp().tm_year<<"."<<wczasy.getDataRozp().tm_mon<<"."<<wczasy.getDataRozp().tm_mday<<
    " ("<<wczasy.getDlugosc()<<" dni)"<<" Koszt: "<<(objazd.getKosztWycieczki()+wczasy.getKosztWycieczki())<<endl;

    plik.close();
}
