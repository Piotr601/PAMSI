#include <iostream>
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

    Graf(Krawedz* krawedz, int l_krawedzi, int l_wierzcholkow)                  // konstruktor grafu
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
        delete[] head;
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
    int l_krawedzi;
    int l_wierzcholkow;
    int pkt_start;
    int i = 0;

    std::fstream plik;

    plik.open("g1.txt", std::ios::in);
    if (plik.good() == false) {
        cout << "\n Plik nie istnieje!!!" << endl;
        exit(1);
    }
    if (plik.good() == true) {
        cout << "Dane z pliku: \n";


        plik >> l_wierzcholkow >> l_krawedzi >> pkt_start;
        cout << l_wierzcholkow << " " << l_krawedzi << " " << pkt_start << endl;

        while (!plik.eof())
            plik >> a[i] >> b[i] >> c[i];
            cout << a[i] << " " << b[i] << " " << c[i] << endl;

        Krawedz krawedz = { a[i], b[i], c[i] };

        i++;


    
        plik.close();
    }
        Lista_Sasiedztwa* kappa;
        Graf g(kappa,l_krawedzi,l_wierzcholkow);

        for (int i = 0; i < l_wierzcholkow; i++)
                g.Wyswietl(g.head[i], i);
      

    

    return 0;
}