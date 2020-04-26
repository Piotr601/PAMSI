﻿#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

#define MAX 200

using namespace std;


struct Lista_Sasiedztwa
{
    int _wierzcholek;                   // numer wierzchołka
    int _waga_krawedzi;                 // numer wagi krawędzi
    struct Lista_Sasiedztwa* nastepny;  // następny element listy
};

struct Krawedz
{
    int pocz;               // Poczatkowy wierzcholek
    int kon;                // Koncowy wierzcholek
    int waga;               // Waga
};

class Graf
{
    Lista_Sasiedztwa* DodajListe(int wierzcholek, int waga_krawedzi, Lista_Sasiedztwa* head) 
    {
        Lista_Sasiedztwa* Lista;

        Lista = new Lista_Sasiedztwa;
        Lista -> _wierzcholek = wierzcholek;
        Lista -> _waga_krawedzi = waga_krawedzi;

        Lista -> nastepny = head;

        return Lista;
    }

  public:

    int l_wierzcholkow;     // liczba wierzcholkow
    int l_krawedzi;         // liczba krawedzi
    
    Lista_Sasiedztwa** head;  // wskaznik na liste sasiedztwa

    Graf(Krawedz krawedz[], int l_krawedzi, int l_wierzcholkow)                  // konstruktor grafu
    {
        Inicjuj(l_wierzcholkow);

        for (int i = 0; i < l_krawedzi; i++) {      // dodanie krawedzi

            int p = krawedz[i].pocz;             // poczatkowy wierzcholek krawedzi
            int k = krawedz[i].kon;              // koncowy wierzcholek krawedzi
            int w = krawedz[i].waga;             // waga krawedzi

            Lista_Sasiedztwa* Lista = DodajListe(k, w, head[p]);   // zainicjowanie poczatku

            head[p] = Lista;   // wskaznik na nowy element
        }
    }

    ~Graf()
    {
        for (int i = 0; i < l_wierzcholkow; i++) {
            delete[] head[i];                      // Zwalnianie pamieci
        }

    }
    
    // Funkcje

    void Inicjuj(int l_wierzcholkow)
    {
        head = new Lista_Sasiedztwa * [l_wierzcholkow];  // rezerowwanie miejsca, tworzenie listw sasiedztwa
        this->l_wierzcholkow = l_wierzcholkow;

        for (int i = 0; i < l_wierzcholkow; ++i)        // inicjalizacja wskaznikow
            head[i] = nullptr;
    }


    void Wyswietl(Lista_Sasiedztwa* wsk, int i)
    {
        while( wsk!=nullptr )
        {
            cout << "(" << i << ", " << wsk->_wierzcholek
                << ", " << wsk->_wierzcholek << ") ";

            wsk = wsk->nastepny;
            cout << endl;
        }
    }
};


int main()
{
    int a[MAX], b[MAX], c[MAX];
    int l_krawedzi = 0; 
    int l_wierzcholkow = 0; 
    int pkt_start = 0;
    std::fstream plik;

    plik.open("g1.txt", std::ios::in);
        if (plik.good() == false) {
            cout << "\n Plik nie istnieje!!!" << endl;
            exit(1);
        }
        if (plik.good() == true) {
            cout << "Dane z pliku: \n";
            int i = 0;
            while (!plik.eof())
            {   

                if (i == 0)
                {
                    plik >> l_wierzcholkow >> l_krawedzi >> pkt_start;
                    cout << l_wierzcholkow << " " << l_krawedzi << " " << pkt_start << endl;
                }

                plik >> a[i] >> b[i] >> c[i];
                cout << a[i] << " " << b[i] << " " << c[i] << endl;

                i++;
            }
            plik.close();
        }

    
     //   cout << "\nLURWA \n";
   /* Krawedz krawedz;

    for (int i = 0; i < l_wierzcholkow; i++) {
        krawedz[i][1] = a[i];
        krawedz[i][2] = b[i];
        krawedz[i][3] = c[i];
    }*/

    Krawedz krawedz[MAX] =
     {
        { 0, 1, 6 }, { 1, 2, 7 }, { 2, 0, 5 }, { 2, 1, 4 },
        { 3, 2, 10 }, { 4, 5, 1 }, { 5, 4, 3 }
     };

    Graf g(krawedz,l_krawedzi,l_wierzcholkow);

    for(int i=0; i< l_wierzcholkow;i++)
        g.Wyswietl(g.head[i],i);

    return 0;
}