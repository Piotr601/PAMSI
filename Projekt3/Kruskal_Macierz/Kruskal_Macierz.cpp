#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

#define max_int 2147483647

using namespace std;

class krawedz {
public:
    int poczatek_k;
    int koniec_k;
    int waga;

    krawedz(int poczatek_k, int koniec_k, int waga)
    {
        this->poczatek_k = poczatek_k;
        this->koniec_k = koniec_k;
        this->waga = waga;
    }

    krawedz() {
        this->poczatek_k = 0;
        this->koniec_k = 0;
        this->waga = 0;
    }

    ~krawedz() {}
};

class Graf
{
private:

    int ilosc_wierzcholkow;
    int** Macierz;

public:

    Graf(int ilosc_wierzcholkow)
    {
        this->ilosc_wierzcholkow = ilosc_wierzcholkow;
        Macierz = new int* [ilosc_wierzcholkow];

        for (int i = 0; i < ilosc_wierzcholkow; i++)
        {
            Macierz[i] = new int[ilosc_wierzcholkow];
            for (int j = 0; j < ilosc_wierzcholkow; j++)
            {
                Macierz[i][j] = 0;
            }
        }
    }

    ~Graf()
    {
        for (int i = 0; i < ilosc_wierzcholkow; i++) {
            delete[] Macierz[i];
        }
        delete[] Macierz;
    }

    void dodaj_krawedz(int x, int y, int waga)
    {
        Macierz[x][y] = waga;
    }

    void usun_krawedz(int x, int y)
    {
        Macierz[x][y] = 0;
    }

    void sprawdzanie_krawedzi(int x, int y)
    {
        if (Macierz[x][y] >= 0)
            cout << "\n Krawedz istnieje\n";
        else
            cout << "\n Krawedz nie istnieje\n";
    }

    void Wyswietl()
    {
        cout << "\n\nGraf: \n";

        for (int i = 0; i < ilosc_wierzcholkow; i++)
        {
            cout << "|" << i << "| ";
            for (int j = 0; j < ilosc_wierzcholkow; j++)
            {
                cout << Macierz[i][j] << "  ";
            }
            cout << endl;
        }

    }

    void ZamienWagi(int x1, int y1, int x2, int y2)
    {
        int waga11 = Macierz[x1][y1];
        int waga12 = Macierz[y1][x1];

        int waga21 = Macierz[x2][y2];
        int waga22 = Macierz[y2][x2];

        Macierz[x2][y2] = waga11;
        Macierz[y2][x2] = waga12;

        Macierz[x1][y1] = waga21;
        Macierz[y1][x1] = waga22;
    }

    // algorytm prime
    void prime()
    {

    }


    // algorytm kruskala
    void kruskal()
    {
        int licznik = 0;
        int index = 0;

        // liczenie krawedzi
        for (int x = 0; x < ilosc_wierzcholkow; x++)
        {
            for (int y = 0; y < ilosc_wierzcholkow; y++)
            {
                if (Macierz[x][y] != 0)
                {
                    licznik++;
                }
            }
        }

        cout << "\nIlosc krawedzi: " << licznik << endl;     // Przy nieskierowanym, nalezy licznik podzielic na 2

        krawedz* kraw = new krawedz[licznik];
        krawedz temp;

        // utworzenie krawedzi i posortowanie wzgledem wag
        for (int i = 0; i < ilosc_wierzcholkow; i++)
        {
            for (int j = i + 1; j < ilosc_wierzcholkow; j++)
            {
                if (Macierz[i][j] > 0) {

                    kraw[index] = krawedz(i, j, Macierz[i][j]);

                    for (int k = index - 1; k >= 0; k--) {

                        if (kraw[k].waga > kraw[k + 1].waga)
                        {
                            temp = kraw[k];
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

        vector<vector<int>> drzewo;
        for (int i = 0; i < licznik; i++)
        {
            index = -1;

            // sprawdzenie czy wystepuje pierwsza krawedz
            for (int j = 0; j < drzewo.size(); j++)
            {
                for (int k = 0; k < drzewo[j].size(); k++)
                {
                    if (kraw[i].poczatek_k == drzewo[j][k])
                    {
                        index = j;
                    }
                }
            }

            // jest pierwszy wierzcholek
            if (index != -1)
            {
                int tem = -1;
                for (int j = 0; j < drzewo.size(); j++)
                {
                    for (int k = 0; k < drzewo[j].size(); k++)
                    {
                        if (kraw[i].koniec_k == drzewo[j][k])
                        {
                            tem = j;
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
                // Nie ma pierwszego wierzcholka
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
        for (int p = 0; p < licznik; p++)
        {
            for (int s = 0; s < licznik; s++)
            {
                if (kraw[p].poczatek_k <= kraw[s].poczatek_k)
                    std::swap(kraw[p], kraw[s]);
            }
        }
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

        cout << "\nMDR: " << sumator << endl;

        delete[] kraw;
    }
};


int main() {

    int ilosc_wierzcholkow, liczba_krawedzi, pkt_startowy;
    int a, b, waga;
    std::fstream plik;

    plik.open("Dane.txt", std::ios::in);
    if (plik.good() == false) {
        cout << "\n Plik nie istnieje!!!" << endl;
        exit(1);
    }

    if (plik.good() == true) {
        //cout << "Dane z pliku: \n";

        plik >> ilosc_wierzcholkow >> liczba_krawedzi >> pkt_startowy;
        //cout << ilosc_wierzcholkow << " " << liczba_krawedzi << " " << pkt_startowy << endl;

        Graf graf(ilosc_wierzcholkow);

        while (!plik.eof())
        {
            plik >> a >> b >> waga;
            // cout << a << " " << b << " " << waga << endl;

            graf.dodaj_krawedz(a, b, waga);

        }
        plik.close();
        
        //graf.dodaj_krawedz(0, 1, 10);
        //graf.usun_krawedz(0, 8);

        //graf.ZamienWagi(0,1,1,2);
        //graf.sprawdzanie_krawedzi(1, 0);

        graf.Wyswietl();


        graf.kruskal();
    }

    return 0;
}