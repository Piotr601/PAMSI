#include <iostream>

using namespace std;

class Szachownica {
    int Szach[8][8];
public:
    Szachownica()
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Szach[x][y] = 0;
            }
        }

        Pionki();
    }

    void Wyświetl()
    {
        for (int y = 0; y < 8; y++)
        {
            cout << " +---+---+---+---+---+---+---+---+" << endl;
            for (int x = 0; x < 8; x++)
            {
                cout << " | " << Szach[x][y];
            }
            cout << " | " << endl;
        }
        cout << " +---+---+---+---+---+---+---+---+" << endl;
    }

    void Pionki()
    {
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 8; x++)
            {
               Szach[x][y] = 1;
            }
        }

        for (int y = 5; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Szach[x][y] = 2;
            }
        }
    }
};

int main()
{
    Szachownica szach;

    szach.Wyświetl();
}