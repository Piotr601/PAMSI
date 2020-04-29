#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

#define MAX 500         // zmienna zdefiniowana MAX do pokazywania wynikow

using namespace std;

// @ struktura krawedz @ 
struct Krawedz
{
    int poczatek_w;     // poczatkowy wierzcholek
    int koniec_w;       // koniec wierzcholka
    int waga;           // waga krawedzi
};

// @ struktura listy @
struct Lista
{
    Lista* nastepny;     // wskaznik na nastepny element
    int waga;            // waga elementu
    int wierzcholek;     // wierzcholek elementu  
};

// @@ klasa Kolejka @@
class Kolejka
{
private:
    Krawedz* Stos;      // tworzenie stosu, gdzie beda przechowywane elementy
    int stos_pozycja;   // pozycja kopca

public:

    Kolejka(int ilosc_krawedzi) // inicjowanie kolejki
    {
        Stos = new Krawedz[ilosc_krawedzi]; // alokowanie pamieci
        stos_pozycja = 0;                   // wyzerowanie pozycji w kopcu
    }

    ~Kolejka()      // destruktor
    {
        delete[] Stos;  // zwalnianie pamieci
    }

    Krawedz poczatek()  // zwraca 1 element kopca
    { 
        return Stos[0]; // zwracanie
    }

    void dodaj(Krawedz kraw)  // dodawanie krawedzi do kolejki
    {
        int poz;            // zmienne 
        int rodzic;

        poz = stos_pozycja++;       // przypisanie pozycji na koniec kopca
        rodzic = (poz - 1) >> 1;    // szukanie rodzica

         // szukanie w kopcu miejsca na krawedz
        while (poz && (Stos[rodzic].waga > kraw.waga))
        {
            Stos[poz] = Stos[rodzic];   // zamiana na kopcu, pozycji z rodzicem
            poz = rodzic;               // zmiana wartosci
            rodzic = (poz - 1) >> 1;    // zmiana pozycji rodzica, przesuniecie bitowe
        }
        Stos[poz] = kraw;       // krawedz wstawiana do kopca
    }

    void usun()      // usuwa krawedz z kopca
    {
        Krawedz kraw;        // stworzenie krawedzi (obiekt)
        int poz = 0;         // zmienne
        int rodzic = 1;

        if (stos_pozycja)   // if (...) oznacza if (...==true), czyli dopoki jest to prawdziwe
        {
            kraw = Stos[--stos_pozycja];     // usuniecie krawedzi z pozycji na kopcu

            while (rodzic < stos_pozycja)    // szukanie nowej pozycji
            {
                if ((rodzic + 1 < stos_pozycja) && (Stos[rodzic + 1].waga < Stos[rodzic].waga))
                        rodzic++;

                if (kraw.waga <= Stos[rodzic].waga)
                    break;

                Stos[poz] = Stos[rodzic];    // przywrocenie wartosci kopca
                poz = rodzic;
                rodzic = (rodzic << 1) + 1;
            }

            Stos[poz] = kraw;   // krawedz usuwana z kopca
        }
    }
    
};

// @@ klasa drzewo @@
class Drzewo
{
private:
    Lista** lista_sasiedztwa;   // tworzenie listy
    int wielkosc;               // wielkosc drzewa-grafu
    int waga_drzewa;            // waga drzewa-grafu

public:

    Drzewo(int rozmiar)         // tworzenie drzewa-jako grafu
    {
        lista_sasiedztwa = new Lista * [rozmiar];   // zarezerwowanie pamieci
        for (int i = 0; i < rozmiar; i++)
        {
            lista_sasiedztwa[i] = nullptr;        //wypelnianie tablicy pustymi wskaznikami
        }
        waga_drzewa = 0;        // wyzerowanie wagi
        wielkosc = rozmiar - 1; // i dlugosci tablicy
    }

    ~Drzewo()
    {
        delete[] lista_sasiedztwa;  // zwolnienie pamieci
    }

    void dodaj_krawedz(Krawedz kraw)    // dodawanie krawedzi do drzewa-grafu
    {
        Lista* Lista1;      // wskaznik na liste

        waga_drzewa += kraw.waga;  // dodawanie wag drzewa rozpinajacego, i krawedzi, ktore sa w nich zawarte

        Lista1 = new Lista;         // stworzenie nowego wezla, jako lista
        Lista1->wierzcholek = kraw.koniec_w;     // przpisanie wierzcholku koncowego krawedzi
        Lista1->waga = kraw.waga;               // przypisanie wagi krawedzi
        Lista1->nastepny = lista_sasiedztwa[kraw.poczatek_w];   //dodawanie do lsity
        lista_sasiedztwa[kraw.poczatek_w] = Lista1;
        
        Lista1 = new Lista;         // stworzenie nowego wezla, jako lista
        Lista1->wierzcholek = kraw.poczatek_w;   // przpisanie wierzcholko poczatkowego krawedzi
        Lista1->waga = kraw.waga;               // przypisanie wagi krawedzi
        Lista1->nastepny = lista_sasiedztwa[kraw.koniec_w]; //dodawanie do lsity
        lista_sasiedztwa[kraw.koniec_w] = Lista1;

    }

    void Wyswietl()  // wyswietlanie drzewa
    {
        cout << "\n";

        Lista* Lista1;  // wskaznik

        int wys1[MAX];  // tablice pomocnicze sluzace do
        int wys2[MAX];  // wyswietlania 
        int wysw[MAX];

        cout << "Algorytm Prime: ";

        for (int i = 0; i <= wielkosc; i++)
        {
            // wypisanie wynikow
            // i= kraw pocz, wierzcholek, kraw konc, waga
            for (Lista1 = lista_sasiedztwa[i]; Lista1; Lista1 = Lista1->nastepny) {
 
               // cout << "\n" << i << " " << Lista1->wierzcholek << " " << Lista1->waga << " ";
                //Przepisanie wynikow do tablic pomocniczych
                wys1[i] = i;
                wys2[i] = Lista1->wierzcholek;
                wysw[i] = Lista1->waga;
            }
            // Wstepne sortowanie i wypisanie
            //if(wys2[i]>=wys1[i])
            cout << "\n" << wys1[i] << " " << wys2[i] << " " << wysw[i];
            //else
            //cout << "\n" << wys2[i] << " " << wys1[i] << " " << wysw[i];
        }

        // wypisanie wartosci Minimalnego Drzewa Rozpinajacego / najkrotsza droga, suma krawedzi w drzewie
        cout << endl << endl;
        cout << "MDR: " << waga_drzewa << endl;
    }

    Lista* poczatek_listy_sasiadow(int rozmiar) // zwracanie wskaznika pozcatku listy sasiadow
    {
        return lista_sasiedztwa[rozmiar];
    }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//               MAIN
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main()
{
    // zainicjowanie wczytywanych elementow
    int l_krawedzi;
    int pkt_start;
    double czas = 0;
    time_t czasStop, czasStart;

    srand(time(NULL));

    int l_wierzcholkow = 1000;            // ustalona liczba wierzcholkow 50 / 100 / 200 / 500 / 1000
    int i_powtorzen = 25;                // ilosc powtorzen algorytmu
    int gestosc = 100;               // gestosc 0,25 / 0.5 / 0.75 / 1.0

    l_krawedzi = (l_wierzcholkow * (l_wierzcholkow - 1) * gestosc) / 200;

    for (int i = 0; i < i_powtorzen; i++)
    {
        pkt_start = rand() % l_wierzcholkow;

        //wczytywanie z pliku
        std::fstream plik;

        plik.open("Dane.txt", std::ios::in);
        if (plik.good() == false) 
        {
            // gdy plik nie istnieje/jest uszkozdony
            cout << "\n Plik nie istnieje!!!" << endl;
            exit(1);
        }

        if (plik.good() == true)
        {
            // gdy plik otworzy sie poprawnie
            // cout << "Dane z pliku: \n";

            ////// ///////// PROGRAM ///////// ////////

                // zczytanie podstawowych wartosci grafu i wypisanie ich
                // z pliku, jest to pierwsza linijka
            // plik >> l_wierzcholkow >> l_krawedzi >> pkt_start;
            // cout << l_wierzcholkow << " " << l_krawedzi << " " << pkt_start << endl;

            // zmienna przechowujaca czy dany wierzcholek zostal juz odwiedzony

            // tworzenie obiektu, kolejki, kopca i drzewa-grafu
            Krawedz kraw;
            Lista* lis;
            Kolejka K(l_krawedzi);
            Drzewo G(l_krawedzi);
            Drzewo D(l_wierzcholkow);
            int* wierzcholki_odwiedzone = new int[l_wierzcholkow];

            // tablica odwiedzin
            for (int i = 0; i <= l_wierzcholkow; i++)
            {
                wierzcholki_odwiedzone[i] = 0;
                if (i == l_wierzcholkow) wierzcholki_odwiedzone[pkt_start] = 1;
            }

            // wczytywanie dalszej czesci pliku,
            // tyle ile wystepuje pozycji = krawedzi
            // a nastepnie dodawanie krawedzi w oparciu o dane do kolejki

            for (int i = 0; i < l_krawedzi; i++)
            {
               //plik >> kraw.poczatek_w >> kraw.koniec_w >> kraw.waga;
               
                // @@@@ TESTY @@@@
                kraw.poczatek_w = rand() % l_wierzcholkow;
                kraw.koniec_w = rand() % l_wierzcholkow;
                kraw.waga = (rand() % 1000) + 1;

                while (kraw.poczatek_w == kraw.koniec_w) {
                    kraw.koniec_w = rand() % l_wierzcholkow;
                }
               
               // cout << kraw.poczatek_w << " " << kraw.koniec_w << " " << kraw.waga << endl;
                G.dodaj_krawedz(kraw);
            }

            // @@@ ALGORYTM @@@
            // MDR graf-drzewo
            czasStart = clock();

            for (int i = 1; i < l_wierzcholkow; i++)
            {
                // lista sasiadow
                for (lis = G.poczatek_listy_sasiadow(pkt_start); lis; lis = lis->nastepny)
                {
                    //jezeli nieodwiedzony == 0 
                    if (wierzcholki_odwiedzone[lis->wierzcholek] == 0)
                    {
                        kraw.poczatek_w = pkt_start;        // tworzona jest krawedz
                        kraw.koniec_w = lis->wierzcholek;
                        kraw.waga = lis->waga;
                        K.dodaj(kraw);                      // dodawana jest do kolejki
                    }
                }

                do {
                    kraw = K.poczatek();              // pobieranie krawedzi z kolejki
                    K.usun();                         // i nastepnie usuwaie jej
                } while (wierzcholki_odwiedzone[kraw.koniec_w] == 1); // dopoki jest w drzewie

                D.dodaj_krawedz(kraw);                        // dodawanie krawedzi do drzewa
                wierzcholki_odwiedzone[kraw.koniec_w] = 1;    // zmiana wierzcholka na odwiedzony
                pkt_start = kraw.koniec_w;                    // ustalamy nowy punkt startowy
            }

            czasStop = clock();
            czas += (double)(czasStop - czasStart) / CLOCKS_PER_SEC;

            /// KONIEC DZIELANIA NA PLIKU
            plik.close();


           // D.Wyswietl();   // wyswietlenie drzewa-grafu
        }
        // cout << i << " ";
    }
    cout << "\nCzas: " << czas / i_powtorzen << endl;
    // KONIEC PROGRAMu
    
    return 0;
}

