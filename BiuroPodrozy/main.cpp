#include <iostream>
#include "BiuroPodrozy.h"
#include <stdlib.h>
using namespace std;

struct tm wczytajDate(char* data_wczytana){
    struct tm data;

    data.tm_year = (data_wczytana[0]-'0')*1000 + (data_wczytana[1]-'0')*100 + (data_wczytana[2]-'0')*10 + (data_wczytana[3]-'0');
    data.tm_mon = (data_wczytana[4]-'0')*10 + (data_wczytana[5]-'0');
    data.tm_mday = (data_wczytana[6]-'0')*10 + (data_wczytana[7]-'0');

    return data;
};

int main(int argc, char **argv){

    char *sciezka;
    char *plik_wyjsciowy;
    char *rodzaj_wycieczki;
    int dlugosc;
    float cena;
    struct tm data;

    if (argc==13){
        for (int i=1; i<argc; i=i+2){
            if ((strcmp(argv[i],"-o"))==0) plik_wyjsciowy = argv[i+1];
            else if ((strcmp(argv[i],"-k"))==0) sciezka = argv[i+1];
            else if ((strcmp(argv[i],"-r"))==0) rodzaj_wycieczki = argv[i+1];
            else if ((strcmp(argv[i],"-d"))==0) dlugosc = atoi(argv[i+1]);
            else if ((strcmp(argv[i],"-t"))==0) data = wczytajDate(argv[i+1]);
            else if ((strcmp(argv[i],"-c"))==0) cena = atof(argv[i+1]);
            else {
                cout <<"Podano zle argumenty programu. Nastepuje zamkniecie programu"<<endl;
                exit(0);
                }
        }

        BiuroPodrozy biuro(sciezka, plik_wyjsciowy, rodzaj_wycieczki, dlugosc, cena, data);
        biuro.czytajPliki();
        biuro.szukajWycieczek();

        cout<<"Oferta biura podrozy zostala wygenerowana i znajduje sie w pliku: "<<plik_wyjsciowy<<endl;
        cout<<"Znaleziono "<<
        biuro.getIloscWycieczek()<<" wycieczek spelniajacych dane kryteria"<<endl;

    }else
        cout<<"Zla ilosc argumentow wywolania programu!! Nastepuje zamkniecie programu!"<<endl;

    return 0;
}
