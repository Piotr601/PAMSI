#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

// @@ klasa krawedz @@
class krawedz {
public:
    int poczatek_k;  // poczatek krawedzi
    int koniec_k;    // koniec krawedzi
    int waga;        // waga krawedzi

    krawedz(int poczatek_k, int koniec_k, int waga) // przepisanie danych do krawdzi
    {
        this->poczatek_k = poczatek_k;
        this->koniec_k = koniec_k;
        this->waga = waga;
    }

    krawedz() 
    {                  // konstruktor do tworzenia krawedzi
        this->poczatek_k = 0;
        this->koniec_k = 0;
        this->waga = 0;
    }

    ~krawedz() {}       // destruktor
};

// @@ klasa graf @@
class Graf
{
private:

    int ilosc_wierzcholkow;     // przechowuje ilosc wierzcholkow
    int** Macierz;              // przechowuje tablice macierzy

public:

    Graf(int ilosc_wierzcholkow)    // tworzenie grafu
    {
        this->ilosc_wierzcholkow = ilosc_wierzcholkow;
        Macierz = new int* [ilosc_wierzcholkow];    // zarezerwowanie pamieci

        for (int i = 0; i < ilosc_wierzcholkow; i++)
        {
            Macierz[i] = new int[ilosc_wierzcholkow];   // zarezerwowanie pamieci
            for (int j = 0; j < ilosc_wierzcholkow; j++)
            {
                Macierz[i][j] = 0;                      // przypisanie wagi 0
            }
        }
    }

    ~Graf()             // usuwanie grafu
    {
        for (int i = 0; i < ilosc_wierzcholkow; i++) {
            delete[] Macierz[i];    // zwalnianie pamieci
        }
        delete[] Macierz;           // zwalnianie pamieci
    }

    void dodaj_krawedz(int x, int y, int waga)  // dodaje kawedz do grafu
    {
        Macierz[x][y] = waga;      // przypisuje wage
    }

    void usun_krawedz(int x, int y)     // usuwa krawedz
    {
        Macierz[x][y] = 0;         // przypisuje wage
    }

    void sprawdzanie_krawedzi(int x, int y)  // sprawdza czy istnieje krawedz
    {
        if (Macierz[x][y] >= 0)                 // jezeli waga jest rozna od 0
            cout << "\n Krawedz istnieje\n";    // to isntieje
        else
            cout << "\n Krawedz nie istnieje\n";
    }

    void Wyswietl()         // wyswietla graf
    {
        cout << "\n\nGraf: \n";

        for (int i = 0; i < ilosc_wierzcholkow; i++)    // przechodzenie po wszystkich i
        {
            cout << "|" << i << "| ";
            for (int j = 0; j < ilosc_wierzcholkow; j++) // przechodzenie po wszystkich j
            {
                cout << Macierz[i][j] << "  ";           // wypisywanie macierzy
            }
            cout << endl;
        }

    }

    void ZamienWagi(int x1, int y1, int x2, int y2) // funkcja zamieniajaca wagi
    {                                               // nalezy podac 1 krawedz i 2 krawedz
        int waga11 = Macierz[x1][y1];          // zapisywanie 1 krawedzi
        int waga12 = Macierz[y1][x1];

        int waga21 = Macierz[x2][y2];           // zapisywanie 2 krawedzi
        int waga22 = Macierz[y2][x2];

        Macierz[x2][y2] = waga11;               // przypisanie ich do innego miejsca
        Macierz[y2][x2] = waga12;               // inaczej zamiana

        Macierz[x1][y1] = waga21;                    
        Macierz[y1][x1] = waga22;
    }


    // @ Algorytm kruskala @
    void kruskal()
    {
        // zmienne
        int licznik = 0;
        int index = 0;

        // liczenie krawedzi
        for (int x = 0; x < ilosc_wierzcholkow; x++)    // przejscie po macierzy
        {
            for (int y = 0; y < ilosc_wierzcholkow; y++)
            {
                if (Macierz[x][y] != 0)
                {
                    licznik++;          // zliczanie
                }
            }
        }
        // wyswietlenie ilosci krawedzi
        cout << "\nIlosc krawedzi: " << licznik << endl;     // Przy nieskierowanym, nalezy licznik podzielic na 2

        // stworzenie nowego obiektu i zarezerwowanie miejsca
        krawedz* kraw = new krawedz[licznik];
        krawedz temp;

        // utworzenie krawedzi i posortowanie wzgledem wag
        for (int i = 0; i < ilosc_wierzcholkow; i++)            // przejscie po macierzy
        {
            for (int j = i + 1; j < ilosc_wierzcholkow; j++)
            {
                if (Macierz[i][j] > 0) {

                    kraw[index] = krawedz(i, j, Macierz[i][j]); // zapisanie krawedzi

                    for (int k = index - 1; k >= 0; k--) {

                        if (kraw[k].waga > kraw[k + 1].waga)    // porownanie wag
                        {
                            temp = kraw[k];                     // zamiana i sortowanie
                            kraw[k] = kraw[k + 1];
                            kraw[k + 1] = temp;
                        }
                    }
                    index++;
                }
            }
        }

        /* Do sprawdzania
        cout << endl;
         for (int p = 0; p < licznik; p++)
          {
              cout << kraw[p].poczatek_k << " " << kraw[p].koniec_k << " " << kraw[p].waga << endl;
          }
        */

        // tworzenie drzewa jako wektor
        vector<vector<int>> drzewo;
        for (int i = 0; i < licznik; i++)
        {
            index = -1;

            // sprawdzenie czy wystepuje pierwsza krawedz w grafie
            for (int j = 0; j < drzewo.size(); j++)         // przejscie
            {
                for (int k = 0; k < drzewo[j].size(); k++)
                {
                    if (kraw[i].poczatek_k == drzewo[j][k]) // jezeli tak to
                    {
                        index = j;                          // zamienia index
                    }
                }
            }

            // sprawdzenie czy pierwszy wierzcholek jest juz w grafie
            if (index != -1)
            {
                int tem = -1;
                for (int j = 0; j < drzewo.size(); j++)         //przejscie
                {
                    for (int k = 0; k < drzewo[j].size(); k++)
                    {
                        if (kraw[i].koniec_k == drzewo[j][k])   // jezeli tak
                        {
                            tem = j;                            // zamiana
                        }
                    }
                }
                // gdy nie ma 2 wierzcholka, dodawanie wierzcholka do istniejacego drzewa
                if (tem == -1)
                {
                    drzewo[index].push_back(kraw[i].koniec_k);
                }
                else if (index != tem)
                {
                    // dodawanie drzewa
                    for (int j = 0; j < drzewo[index].size(); j++)
                    {
                        drzewo[tem].push_back(drzewo[index][j]);
                    }
                    // usuwanie drzewa
                    drzewo.erase(drzewo.begin() + index);
                }
                else
                {
                    //usuwanie krawedzi
                    kraw[i] = krawedz(-1, -1, -1);

                }
            }

            else
            {
                // gdy nie ma pierwszego wierzcholka w grafie 
                for (int j = 0; j < drzewo.size(); j++)
                {
                    for (int k = 0; k < drzewo[j].size(); k++)
                    {
                        if (kraw[i].koniec_k == drzewo[j][k])
                        {
                            index = j;
                        }
                    }
                }
                // Gdy wierzcholek jest w innym drzewie
                if (index != -1)
                {
                    drzewo[index].push_back(kraw[i].poczatek_k);
                }
                // kiedy nie ma zadnego wierzcholka w zadnym drzewie
                else
                {
                    // tworzenie nowego drzewa
                    drzewo.push_back(vector<int>());

                    // dodawanie wierzcholkow do drzewa
                    drzewo[drzewo.size() - 1].push_back(kraw[i].poczatek_k);
                    drzewo[drzewo.size() - 1].push_back(kraw[i].koniec_k);

                }
            }

        }

        // sortowanie wynikow
       /* for (int p = 0; p < licznik; p++)
        {
            for (int s = 0; s < licznik; s++)
            {
                if (kraw[p].poczatek_k <= kraw[s].poczatek_k)
                    std::swap(kraw[p], kraw[s]);
            }
        }*/
        // zalecane dla duzych plikow quicksort V


        int sumator = 0;

        // wypisanie wynikow
        cout << endl;
        for (int p = 0; p < licznik; p++)
        {
            if (kraw[p].waga != -1) {
                sumator += kraw[p].waga;
                cout << kraw[p].poczatek_k << " " << kraw[p].koniec_k << " " << kraw[p].waga << endl;
            }
        }
        // wypisanie minimalnego drzewa rozpinajacego
        cout << "\nMDR: " << sumator << endl;

        delete[] kraw;
    }
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//               MAIN
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

int main() {
    // zainicjowanie wczytywanych elementow
    int ilosc_wierzcholkow, liczba_krawedzi, pkt_startowy;
    int a, b, waga;

    // wczytywanie z pliku 
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
       
        // zczytanie podstawowych wartosci grafu i wypisanie ich
        // z pliku, jest to pierwsza linijka

        //cout << "Dane z pliku: \n";
        plik >> ilosc_wierzcholkow >> liczba_krawedzi >> pkt_startowy;
        //cout << ilosc_wierzcholkow << " " << liczba_krawedzi << " " << pkt_startowy << endl;

        // tworzenie obiektu - graf
        Graf graf(ilosc_wierzcholkow);

        // wczytywanie dalszej czesci pliku,
        // tyle ile wystepuje pozycji = krawedzi
        // a nastepnie dodawanie krawedzi do grafu

        for (int i = 0; i < liczba_krawedzi; i++) {

            plik >> a >> b >> waga;
           // cout << a << " " << b << " " << waga << endl;

            graf.dodaj_krawedz(a, b, waga);

        }
        /// KONIEC DZIELANIA NA PLIKU
        plik.close();
        
        // INNE FUNKCJE
            //graf.dodaj_krawedz(0, 1, 10);
            //graf.usun_krawedz(0, 8);

            //graf.ZamienWagi(0,1,1,2);
            //graf.sprawdzanie_krawedzi(1, 0);

        // Wyswietla graf
        //graf.Wyswietl();

        // @@@ Algorytm @@@
        graf.kruskal();
    }

    return 0;
}