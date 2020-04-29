#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

#define MAX 500

using namespace std;

struct Krawedz
{
    int poczatek_w;     // poczatkowy wierzcholek
    int koniec_w;       // koniec wierzcholka
    int waga;           // waga krawedzi
};

struct Lista
{
    Lista* nastepny;
    int waga;
    int wierzcholek;
};


class Drzewo
{
private:
    Lista** lista_sasiedztwa;
    int wielkosc;
    int waga_drzewa;

public:

    Drzewo(int rozmiar)
    {
        lista_sasiedztwa = new Lista * [rozmiar];
        for (int i = 0; i < rozmiar; i++)
        {
            lista_sasiedztwa[i] = nullptr;
        }
        waga_drzewa = 0;
        wielkosc = rozmiar - 1;
    }

    ~Drzewo()
    {
        delete[] lista_sasiedztwa;
    }

    void dodaj_krawedz(Krawedz kraw)
    {
        Lista* Lista1;

        waga_drzewa += kraw.waga;

        Lista1 = new Lista;
        Lista1->wierzcholek = kraw.koniec_w;
        Lista1->waga = kraw.waga;
        Lista1->nastepny = lista_sasiedztwa[kraw.poczatek_w];
        lista_sasiedztwa[kraw.poczatek_w] = Lista1;
        
        Lista1 = new Lista;
        Lista1->wierzcholek = kraw.poczatek_w;
        Lista1->waga = kraw.waga;
        Lista1->nastepny = lista_sasiedztwa[kraw.koniec_w];
        lista_sasiedztwa[kraw.koniec_w] = Lista1;

    }

    void Wyswietl()
    {
        cout << "\n";

        Lista* Lista1;

        int wys1[MAX];
        int wys2[MAX];
        int wysw[MAX];

        cout << "Algorytm Prime: ";

        for (int i = 0; i <= wielkosc; i++)
        {
            for (Lista1 = lista_sasiedztwa[i]; Lista1; Lista1 = Lista1->nastepny) {
 
               // cout << "\n" << i << " " << Lista1->wierzcholek << " " << Lista1->waga << " ";
                wys1[i] = i;
                wys2[i] = Lista1->wierzcholek;
                wysw[i] = Lista1->waga;
            }
            
            //if(wys2[i]>=wys1[i])
            cout << "\n" << wys1[i] << " " << wys2[i] << " " << wysw[i];
            //else
            //cout << "\n" << wys2[i] << " " << wys1[i] << " " << wysw[i];


        }

        cout << endl << endl;
        cout << "MDR: " << waga_drzewa << endl;
    }

    Lista* poczatek_listy_sasiadow(int rozmiar)
    {
        return lista_sasiedztwa[rozmiar];
    }
};

//Kolejka priorytetowa

class Kolejka
{
private:
    Krawedz* Stos;
    int stos_pozycja;

public:
    Krawedz poczatek()
    { 
        return Stos[0];
    }

    Kolejka(int ilosc_krawedzi)
    {
        Stos = new Krawedz[ilosc_krawedzi];
        stos_pozycja = 0;
    }

    ~Kolejka()
    {
        delete[] Stos;
    }

    void dodaj(Krawedz kraw)
    {
        int poz;
        int rodzic;

        poz = stos_pozycja++;
        rodzic = (poz - 1) >> 1;

        // przeszukiwaniu kopca w celu znaleznienia miejsca
        while (poz && (Stos[rodzic].waga > kraw.waga))
        {
            Stos[poz] = Stos[rodzic];
            poz = rodzic;
            rodzic = (poz - 1) >> 1;
        }
        Stos[poz] = kraw;
    }

    void usun()
    {
        Krawedz kraw;
        int poz;
        int rodzic;

        if (stos_pozycja)
        {
            poz = 0;
            rodzic = 1;

            kraw = Stos[--stos_pozycja];

            while (rodzic < stos_pozycja)
            {
                if ((rodzic + 1 < stos_pozycja) && (Stos[rodzic + 1].waga < Stos[rodzic].waga))
                        rodzic++;

                if (kraw.waga <= Stos[rodzic].waga)
                    break;

                Stos[poz] = Stos[rodzic];
                poz = rodzic;
                rodzic = (rodzic << 1) + 1;
            }

            Stos[poz] = kraw;
        }
    }
    
};


int main()
{

    int l_krawedzi;
    int l_wierzcholkow;
    int pkt_start;

    std::fstream plik;

    plik.open("Dane.txt", std::ios::in);
    if (plik.good() == false) {
        cout << "\n Plik nie istnieje!!!" << endl;
        exit(1);
    }

    if (plik.good() == true) {
        cout << "Dane z pliku: \n";

        ///////// PROGRAM ///////////////


        plik >> l_wierzcholkow >> l_krawedzi >> pkt_start;
        cout << l_wierzcholkow << " " << l_krawedzi << " " << pkt_start << endl;

        Krawedz kraw;
        Lista* lis;
        int* odwiedzony = new int[l_wierzcholkow];
        Kolejka K(l_krawedzi);
        Drzewo G(l_krawedzi);
        Drzewo D(l_wierzcholkow);

        for (int i = 0; i <= l_wierzcholkow; i++)
        {
            odwiedzony[i] = 0;
            if (i == l_wierzcholkow) odwiedzony[pkt_start] = 1;
        }

        for (int i = 0; i < l_krawedzi; i++)
        {
                plik >> kraw.poczatek_w >> kraw.koniec_w >> kraw.waga;
                cout << kraw.poczatek_w << " " << kraw.koniec_w << " " << kraw.waga << endl;
                G.dodaj_krawedz(kraw);
        }

        for (int i = 1; i < l_wierzcholkow; i++)
        {
            for (lis = G.poczatek_listy_sasiadow(pkt_start); lis; lis = lis->nastepny)
            {
                if (odwiedzony[lis->wierzcholek]==0)
                {
                    kraw.poczatek_w = pkt_start;
                    kraw.koniec_w = lis->wierzcholek;
                    kraw.waga = lis->waga;
                    K.dodaj(kraw);
                }
            }

            do {
                kraw = K.poczatek();
                K.usun();
            } while (odwiedzony[kraw.koniec_w] == 1);

            D.dodaj_krawedz(kraw);
            odwiedzony[kraw.koniec_w] = 1;
            pkt_start = kraw.koniec_w;

        }

        D.Wyswietl();
        plik.close();
    }
    
    
    return 0;
}

