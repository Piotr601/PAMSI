#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>

#define MAX 50

using namespace std;

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
        Macierz[y][x] = waga;
        Macierz[x][y] = waga;
    }

    void usun_krawedz(int x, int y)
    {
        Macierz[y][x] = 0;
        Macierz[x][y] = 0;
    }

    void sprawdzanie_krawedzi(int x, int y)
    {
        if (Macierz[x][y] != 0)
            cout << "\n Krawedz istnieje\n";
        else
            cout << "\n Krawedz nie istnieje\n";
    }

    void Wyswietl()
    {
        cout << "\n\nGraf: \n";

        for (int i = 0; i < ilosc_wierzcholkow; i++)
        {
            cout << i << " .   ";
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

};


int main() {

    int ilosc_wierzcholkow, liczba_krawedzi, pkt_startowy;
    int a, b, waga;
    std::fstream plik;

    plik.open("g1.txt", std::ios::in);
    if (plik.good() == false) {
        cout << "\n Plik nie istnieje!!!" << endl;
        exit(1);
    }
    if (plik.good() == true) {
        cout << "Dane z pliku: \n";

        plik >> ilosc_wierzcholkow >> liczba_krawedzi >> pkt_startowy;
        //cout << ilosc_wierzcholkow << " " << liczba_krawedzi << " " << pkt_startowy << endl;
            

        Graf graf(ilosc_wierzcholkow);

        while (!plik.eof())
        {

            plik >> a >> b >> waga;
            //cout << a << " " << b << " " << waga << endl;

            graf.dodaj_krawedz(a, b, waga);
            
        }
        plik.close();
        

        graf.usun_krawedz(0, 1);

        //graf.ZamienWagi(0,1,1,2);

        graf.Wyswietl();

        graf.sprawdzanie_krawedzi(1, 0);
        
    }
    

    cout << "\n";


    return 0;
}