#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

// @ struktura krawedzi @
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

// @ struktura minimalnego_drzewa_rozpinajacego @
struct MDR
{
    int rodzic;         // rodzic - kopiec
    int rząd;           // rzad - dlugosc w kopcu
};

// @@ klasa kolejka @@
class Kolejka
{
private:
    Krawedz* Stos;      // tworzenie stosu, gdzie beda przechowywane elementy
    int stos_pozycja;   // pozycja kopca

public:
    Kolejka(int ilosc_krawedzi)             // inicjowanie kolejki
    {
        Stos = new Krawedz[ilosc_krawedzi]; // alokowanie pamieci
        stos_pozycja = 0;                   // wyzerowanie pozycji w kopcu
    }

    ~Kolejka()              // destruktor
    {
        delete[] Stos;      // zwalnianie pamieci
    }

    Krawedz poczatek()      // zwraca 1 element kopca
    {
        return Stos[0];     // zwracanie
    }

    void dodaj(Krawedz kraw)        // dodawanie krawedzi do kolejki
    {
        int poz;                    // zmienne 
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

    void usun()             // usuwa krawedz z kopca
    {
        Krawedz kraw;        // stworzenie krawedzi (obiekt)
        int poz = 0;         // zmienne
        int rodzic = 1;

        if (stos_pozycja)       // if (...) oznacza if (...==true), czyli dopoki jest to prawdziwe
        {
            kraw = Stos[--stos_pozycja];    // usuniecie krawedzi z pozycji na kopcu

            while (rodzic < stos_pozycja)   // szukanie nowej pozycji
            {
                
                if ((rodzic + 1 < stos_pozycja) && (Stos[rodzic + 1].waga < Stos[rodzic].waga))
                    rodzic++;

                if (kraw.waga <= Stos[rodzic].waga)
                    break;

                Stos[poz] = Stos[rodzic];   // przywrocenie wartosci kopca
                poz = rodzic;
                rodzic = (rodzic << 1) + 1;
            }

            Stos[poz] = kraw;   // krawedz usuwana z kopca
        }
    }
};

// @@ klasa struktura_obiektow, odnoszaca sie do struktury MDR @@
class Struktura_obiektow
{
private:
    MDR* struktura;         // Stworzenie nowej listy

public:
    Struktura_obiektow(int wierzcholek) // stworzenie listy
    {
        struktura = new MDR[wierzcholek];  // zarezerwowanie pamieci
    }

    ~Struktura_obiektow()  // usuwanie listy
    {
        delete[] struktura; // zwalnianie pamieci
    }

    void Inicjuj(int wierzcholek) // zainicjowanie listy
    {
        struktura[wierzcholek].rodzic = wierzcholek;   // nadanie im wartosci
        struktura[wierzcholek].rząd = 0;               // nadanie wartosci
    }

    int Znajdz(int wierzcholek) // szuka w liscie
    {
        // rekurancja - poszukiwanie
        if (struktura[wierzcholek].rodzic != wierzcholek) {
            struktura[wierzcholek].rodzic = Znajdz(struktura[wierzcholek].rodzic);
        }
        // zwracany jest juz znaleziony element
        return struktura[wierzcholek].rodzic;
    }

    void Polacz(Krawedz kraw)    // laczy 2 struktury
    {
        int s1;             // struktura 1
        int s2;             // struktura 2

        s1 = Znajdz(kraw.poczatek_w);   // korzen drzewa z wezlem s1 (poczatek krawedzi)
        s2 = Znajdz(kraw.koniec_w);     // korzen drzewa z wezlem s2 (koniec krawedz)

        if (s1 != s2)       // sprawdzanie czy korzenie sa rozne
        {
            if (struktura[s1].rząd > struktura[s2].rząd) // porownanie rzedow drzew
            {
                struktura[s2].rodzic = s1;    // gdy s2 wieksze, to dolaczamy s1
            }
            else struktura[s1].rodzic = s2;   // w przeciwnym razie do s1 dolaczamy s2

            if (struktura[s1].rodzic == struktura[s2].rodzic) // jezeli sa takie same, to  ziwkeszany jest rzad drzewa
                struktura[s2].rząd++;   // zwiekszanie
            
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
            lista_sasiedztwa[i] = nullptr;      //wypelnianie tablicy pustymi wskaznikami
        }
        waga_drzewa = 0;        // wyzerowanie wagi
        wielkosc = rozmiar - 1; // i dlugosci tablicy
    }

    ~Drzewo()
    {
        delete[] lista_sasiedztwa;      // zwolnienie pamieci
    }

    void dodaj_krawedz(Krawedz kraw)    // dodawanie krawedzi do drzewa-grafu
    {
        Lista* Lista1;          // wskaznik na liste

        waga_drzewa += kraw.waga;   // dodawanie wag drzewa rozpinajacego, i krawedzi, ktore sa w nich zawarte

        Lista1 = new Lista;         // stworzenie nowego wezla, jako lista
        Lista1->wierzcholek = kraw.koniec_w;    // przpisanie wierzcholko koncowego krawedzi
        Lista1->waga = kraw.waga;               // przypisanie wagi krawedzi
        Lista1->nastepny = lista_sasiedztwa[kraw.poczatek_w];   //dodawanie do lsity
        lista_sasiedztwa[kraw.poczatek_w] = Lista1;

    }

    void Wyswietl()         // wyswietlanie drzewa
    {
        Lista* Lista1;      //wskaznik
        cout << "Algorytm Kruskala: \n";
        for (int i = 0; i <= wielkosc; i++)
        {
            // wypisanie wynikow
            // i= kraw pocz, wierzcholek, kraw konc, waga
            for (Lista1 = lista_sasiedztwa[i]; Lista1; Lista1 = Lista1->nastepny)
                cout << "\n" << i << " " << Lista1->wierzcholek << " " << Lista1->waga << " ";

        }
        // wypisanie wartosci Minimalnego Drzewa Rozpinajacego / najkrotsza droga, suma krawedzi w drzewie
        cout << "\n\nMDR: " << waga_drzewa << endl;
    }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//               MAIN
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main()
{   //   @@@@ @@@@ TESTY @@@@ @@@@    //
    // zainicjowanie wczytywanych elementow
    int l_krawedzi;
    int pkt_start;
    int temp1, temp2, temp3;
    double czas=0;
    time_t czasStop, czasStart;

    srand(time(NULL));

    int l_wierzcholkow = 1000;            // ustalona liczba wierzcholkow 50 / 100 / 200 / 500 / 1000
    int i_powtorzen = 100;                // ilosc powtorzen algorytmu
    int gestosc = 25;               // gestosc 0,25 / 0.5 / 0.75 / 1.0

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
            //plik >> l_wierzcholkow >> l_krawedzi >> pkt_start;

        // ustalana wartosc
           // cout << "W1 W2 PS\n";
           // cout << l_wierzcholkow << " " << l_krawedzi << " " << pkt_start << endl;
            // pomija pierwsza linie
               // plik >> temp1 >> temp2 >> temp3;
               // cout << temp1 << " " << temp2 << " " << temp3 << endl;

                /// KONIEC DZIELANIA NA PLIKU
            plik.close();

            // tworzenie obiektu, kolejki, kopca i drzewa-grafu
            Krawedz kraw;
            Kolejka K(l_krawedzi);
            Drzewo D(l_wierzcholkow);
            Struktura_obiektow S(l_wierzcholkow);

            // zainicjowanie struktur
            for (int i = 0; i < l_wierzcholkow; i++)
            {
                S.Inicjuj(i);
            }

            // wczytywanie dalszej czesci pliku,
            // tyle ile wystepuje pozycji = krawedzi
            // a nastepnie dodawanie krawedzi w oparciu o dane do kolejki

            for (int i = 0; i < l_krawedzi; i++) {
                // plik >> kraw.poczatek_w >> kraw.koniec_w >> kraw.waga;

                // @@@@ TESTY @@@@
                kraw.poczatek_w = rand() % l_wierzcholkow;
                kraw.koniec_w = rand() % l_wierzcholkow;
                kraw.waga = (rand() % 1000) + 1;

                while (kraw.poczatek_w == kraw.koniec_w) {
                    kraw.koniec_w = rand() % l_wierzcholkow;
                }

                K.dodaj(kraw);

                //  wypisanie wczytywanych danych
               // cout << kraw.poczatek_w << " " << kraw.koniec_w << " " << kraw.waga << endl;

            }

            // @@@ Algorytm @@@
            czasStart = clock();
            for (int i = 1; i < l_wierzcholkow; i++)
            {
                do
                {
                    kraw = K.poczatek();    // pobieranie z kolejki krawedzi
                    K.usun();           // usuwanie z kolejki krawedzi
                } while (S.Znajdz(kraw.poczatek_w) == S.Znajdz(kraw.koniec_w));

                D.dodaj_krawedz(kraw);      // dodawanie krawedzi do drzewa
                S.Polacz(kraw);             // laczenie drzew  wstrukturze
            }

            czasStop = clock();
        czas += (double)(czasStop-czasStart)/CLOCKS_PER_SEC;

            // wyswietlanie drzewa
            // D.Wyswietl();
        //cout << i;
        }
    }
    cout << "\nCzas: " << czas/i_powtorzen << endl;
    // KONIEC PROGRAMu

    return 0;
}