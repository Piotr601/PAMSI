#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

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

struct MDR
{
    int rodzic;
    int rząd;
};

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

        if(stos_pozycja == true)
        {
            poz = 0;
            rodzic = 1;

            kraw = Stos[--stos_pozycja];
            
            while (rodzic < stos_pozycja)
            {
                if (rodzic + 1 < stos_pozycja)
                {
                    if (Stos[rodzic + 1].waga < Stos[rodzic].waga)
                        rodzic++;
                }

                if (kraw.waga <= Stos[rodzic].waga)
                    break;
                
                Stos[poz] = Stos[rodzic];
                poz = rodzic;
                rodzic = (1 << 1) + 1;
            }

            Stos[poz] = kraw;
        }
    }
};

class Struktura_obiektow
{
    private:
    MDR* struktura;

    public:
        Struktura_obiektow(int wierzcholek)
        {
            struktura = new MDR[wierzcholek];
        }
        
        ~Struktura_obiektow()
        {
            delete[] struktura;
        }

        void Inicjuj(int wierzcholek)
        {
            struktura[wierzcholek].rząd = 0;
            struktura[wierzcholek].rodzic = wierzcholek;
        }

        int Znajdz(int wierzcholek)
        {
            if (wierzcholek != struktura[wierzcholek].rodzic) {
                struktura[wierzcholek].rodzic = Znajdz(struktura[wierzcholek].rodzic);
            }

            return struktura[wierzcholek].rodzic;
        }

        void Polacz(Krawedz kraw)
        {
            int s1;             // struktura 1
            int s2;             // struktura 2

            s1 = Znajdz(kraw.poczatek_w);
            s2 = Znajdz(kraw.koniec_w);

            if (s1 != s2)
            {
                if (struktura[s1].rząd > struktura[s2].rząd)
                {
                    struktura[s2].rodzic = s1;
                }
                else
                {
                    struktura[s1].rodzic = s2;

                    if (struktura[s1].rodzic == struktura[s2].rodzic)
                        struktura[s2].rząd++;
                }
            }
        }
};

class Drzewo
{
    private:
        Lista** lista_sasiedztwa;
        int wielkosc;

    public:
        int waga_drzewa;

        Drzewo(int rozmiar) 
        {
            lista_sasiedztwa = new Lista *[rozmiar];
            for (int i = 0; i < rozmiar; i++)
            {
                lista_sasiedztwa = NULL;
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
            Lista1 = new Lista;

            waga_drzewa += kraw.waga;
            
            Lista1->wierzcholek = kraw.koniec_w;
            Lista1->waga = kraw.waga;
            Lista1->nastepny = lista_sasiedztwa[kraw.poczatek_w];
            lista_sasiedztwa[kraw.poczatek_w] = Lista1;

        }

        void Wyswietl()
        {
            cout << "\n";

            Lista* Lista1;

            for (int i = 0; i <= wielkosc; i++)
            {
                cout << "i";
                for (Lista1 = lista_sasiedztwa[i]; Lista1; Lista1 = Lista1->nastepny)
                    cout << " " << Lista1->wierzcholek << ":" << Lista1->waga << " ";
                
                cout << endl;
            }
            
            cout << endl << endl;
            cout << "MDR: " << waga_drzewa << endl;
        }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

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

        Krawedz kraw;

        plik >> l_wierzcholkow >> l_krawedzi >> pkt_start;
        cout << l_wierzcholkow << " " << l_krawedzi << " " << pkt_start << endl;
       
        Kolejka K(l_krawedzi);
        Drzewo D(l_wierzcholkow);
        Struktura_obiektow S(l_wierzcholkow);

        for (int i = 0; i < l_wierzcholkow; i++)
        {
            S.Inicjuj(i);
        }

        while (!plik.eof()) {
            for (int i = 0; i < l_krawedzi; i++)
            {
                plik >> kraw.poczatek_w >> kraw.koniec_w >> kraw.waga;
               // cout << kraw.poczatek_w << " " << kraw.koniec_w << " " << kraw.waga << endl;
            
                K.dodaj(kraw);

            }

        }
        
        for (int i = 1; i < l_wierzcholkow; i++)
        {
            do
            {
                kraw = K.poczatek();
                K.usun();
            } while (S.Znajdz(kraw.poczatek_w) == S.Znajdz(kraw.koniec_w));

            D.dodaj_krawedz(kraw);
            S.Polacz(kraw);
        }

        D.Wyswietl();

        plik.close();
    }

    return 0;
}