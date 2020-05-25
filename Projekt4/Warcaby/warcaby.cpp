#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>

using namespace std;

int Szach[8][8];

int wygrana_b = 0;
int wygrana_c = 0;
int remis = 0;
int px;
int py;
int tura;
char pxlitera;


struct Szachownica
{
    Szachownica()
    {
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                Szach[x][y] = 0;
            }
        }
    }

    void Wyświetl()
    {
        cout << "      A   B   C   D   E   F   G   H" << endl;
        for (int y = 0; y < 8; y++)
        {
            cout << "    +---+---+---+---+---+---+---+---+" << endl << " " << y << " ";;
            for (int x = 0; x < 8; x++)
            {
                cout << " | ";

                if (Szach[x][y] == 0 || Szach[x][y] == 3) cout << " ";
                if (Szach[x][y] == 1) cout << "o";
                if (Szach[x][y] == 2) cout << "0";

            }
            cout << " | " << endl;
        }
        cout << "    +---+---+---+---+---+---+---+---+" << endl;
    }
};

class Pionki {
public:
    Pionki() {
        Pionki_Biale();
        Pionki_Czarne();
        Pola_Wolne();
    }

    void Pionki_Biale() {
        for (int y = 5; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (y % 2 == 0)
                {
                    if (x % 2 != 0)
                        Szach[x][y] = 1;
                    else
                        Szach[x][y] = 0;
                }
                else
                {
                    if (x % 2)
                        Szach[x][y] = 0;
                    else
                        Szach[x][y] = 1;
                }
            }
        }
    }

    void Pionki_Czarne() {
        for (int y = 0; y < 3; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (y % 2 == 0)
                {
                    if (x % 2 != 0)
                        Szach[x][y] = 2;
                    else
                        Szach[x][y] = 0;
                }
                else
                {
                    if (x % 2)
                        Szach[x][y] = 0;
                    else
                        Szach[x][y] = 2;
                }
            }
        }
    }

    void Pola_Wolne() {
        for (int y = 3; y < 5; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                if (y % 2 == 0)
                {
                    if (x % 2 != 0)
                        Szach[x][y] = 3;
                    else
                        Szach[x][y] = 0;
                }
                else
                {
                    if (x % 2)
                        Szach[x][y] = 0;
                    else
                        Szach[x][y] = 3;
                }
            }
        }
    }

    void Wybierz_Pionka(char pxlitera, int py)
    {

        if ((py >= 0 && py < 8) && ( (pxlitera == 'A') || (pxlitera == 'B') || (pxlitera == 'C') || (pxlitera == 'D') || (pxlitera == 'E') || (pxlitera == 'F') || (pxlitera == 'G') || (pxlitera == 'H') ) )
        {
            //cout << "Wybrano (" << pxlitera << "," << py << ") ";

            if (pxlitera == 'A')
                px = 0;
            if (pxlitera == 'B')
                px = 1;
            if (pxlitera == 'C')
                px = 2;
            if (pxlitera == 'D')
                px = 3;
            if (pxlitera == 'E')
                px = 4;
            if (pxlitera == 'F')
                px = 5;
            if (pxlitera == 'G')
                px = 6;
            if (pxlitera == 'H')
                px = 7;

           /* if (Szach[px][py] == 1)
                cout << " > Wybrano (" << px << "," << py << ") ";
            if (Szach[px][py] == 2)
                cout << " > Wybrano (" << px << "," << py << ") ";
            if (Szach[px][py] == 3)
                cout << " Puste pole"; 
            if (Szach[px][py] == 4)
                cout << "";*/

        }
        else
        {
            cout << "Wprowadzono niepoprawne wspolrzedne, prosze sprobowac jeszcze raz\n";
            Sleep(500);
        }
    }

    void Ruch_Pionka_bialy()
    {
        int ruch = 0;

        Poczatek:
        cout << "\nPodaj namiary na pionka wpisujac rzad i kolumne, np (A1)" << endl << ">> ";
        cin >> pxlitera >> py;

        Wybierz_Pionka(pxlitera, py);

            if (Szach[px][py] == 1)
            {
                int licznik_ruchow = 1;
                int bicie = 0;

                // Bicie pionka biale

                if (Szach[px - 1][py - 1] == 2)
                {
                    if (Szach[px - 2][py - 2] == 3)
                    {
                        cout << " 1 bicie: " << "(" << px - 2 << "," << py - 2 << ")        ";
                        bicie++;
                    }
                }

                if (Szach[px - 1][py + 1] == 2)
                {
                    if (Szach[px - 2][py + 2] == 3)
                    {
                        cout << " 2 bicie: " << "(" << px - 2 << "," << py + 2 << ")        ";
                        bicie++;
                    }
                }

                if (Szach[px + 1][py - 1] == 2)
                {
                    if (Szach[px + 2][py - 2] == 3)
                    {
                        cout << " 3 bicie: " << "(" << px + 2 << "," << py - 2 << ")        ";
                        bicie++;
                    }
                }

                if (Szach[px + 1][py + 1] == 2)
                {
                    if (Szach[px + 2][py + 2] == 3)
                    {
                        cout << " 4 bicie: " << "(" << px + 2 << "," << py + 2 << ")        ";
                        bicie++;
                    }
                }

               
                cout << endl;

                //Sprawdzanie ruchow po wolnych polach

                cout << "\nMozliwe ruchy: \n";


                if (Szach[px - 1][py + 1] == 3)
                {
                    cout << " 5 DL: " << "(" << px - 1 << "," << py + 1 << ")        ";
                    licznik_ruchow++;
                }

                if (Szach[px + 1][py + 1] == 3)
                {
                    cout << " 6 DR: " << "(" << px + 1 << "," << py + 1 << ")        ";
                    licznik_ruchow++;
                }

                if (Szach[px - 1][py - 1] == 3)
                {
                    cout << " 7 UL: " << "(" << px - 1 << "," << py - 1 << ")        ";
                    licznik_ruchow++;
                }

                if (Szach[px + 1][py - 1] == 3)
                {
                    cout << " 8 UR: " << "(" << px + 1 << "," << py - 1 << ")        ";
                    licznik_ruchow++;
                }

                // Gdy nie ma zadnego ruchu i bicia
                if (licznik_ruchow - 1 == 0 && bicie == 0)
                {
                    cout << " X Brak ruchow dla tego pionka\n";
                    Sleep(100);
                    goto Poczatek;
                }
                else
                {

                    cout << " 9 - cofnij        ";
                    cout << "\nWpisz ktory ruch chcesz wykonac: ";
                    cin >> ruch;

                    // BICIA biale
                    if (ruch == 1)
                    {
                        std::swap(Szach[px - 2][py - 2], Szach[px][py]);
                        Szach[px - 1][py - 1] = 3;
                    }

                    if (ruch == 2)
                    {
                        std::swap(Szach[px - 2][py + 2], Szach[px][py]);
                        Szach[px - 1][py + 1] = 3;
                    }

                    if (ruch == 3)
                    {
                        std::swap(Szach[px + 2][py - 2], Szach[px][py]);
                        Szach[px + 1][py - 1] = 3;
                    }

                    if (ruch == 4)
                    {
                        std::swap(Szach[px + 2][py + 2], Szach[px][py]);
                        Szach[px + 1][py + 1] = 3;
                    }
                    
                    // RUCHY biale
                    if (ruch == 5)
                    {
                        std::swap(Szach[px - 1][py + 1], Szach[px][py]);
                    }

                    if (ruch == 6)
                    {
                        std::swap(Szach[px + 1][py + 1], Szach[px][py]);
                    }

                    if (ruch == 8)
                    {
                        std::swap(Szach[px + 1][py - 1], Szach[px][py]);
                    }

                    if (ruch == 7)
                    {
                        std::swap(Szach[px - 1][py - 1], Szach[px][py]);
                    }

                    if (ruch == 9)
                    {
                        goto Poczatek;
                    }
                }
            }
            else
            {
                cout << "Wybierz bialy pionek!";
                Sleep(150);
                goto Poczatek;
            }
            
    }

    void Ruch_Pionka_czarny()
    {
        int ruch = 0;


        Poczatek:
        cout << "\nPodaj namiary na pionka wpisujac rzad i kolumne, np (A1)" << endl << ">> ";
        cin >> pxlitera >> py;

        Wybierz_Pionka(pxlitera, py);

            if (Szach[px][py] == 2)
            {
                int licznik_ruchow = 1;
                int bicie = 0;

                //Sprawdzenie bicia czarne

                if (Szach[px - 1][py - 1] == 1)
                {
                    if (Szach[px - 2][py - 2] == 3)
                    {
                        cout << " 1 bicie: " << "(" << px - 2 << "," << py - 2 << ")        ";
                        bicie++;

                    }
                }

                if (Szach[px - 1][py + 1] == 1)
                {
                    if (Szach[px - 2][py + 2] == 3)
                        cout << " 2 bicie: " << "(" << px - 2 << "," << py + 2 << ")        ";
                        bicie++;

                }

                if (Szach[px + 1][py - 1] == 1)
                {
                    if (Szach[px + 2][py - 2] == 3)
                    {
                        cout << " 3 bicie: " << "(" << px + 2 << "," << py - 2 << ")        ";
                        bicie++;
                    }
                }

                if (Szach[px + 1][py + 1] == 1)
                {
                    if (Szach[px + 2][py + 2] == 3)
                    {
                        cout << " 4 bicie: " << "(" << px + 2 << "," << py + 2 << ")        ";
                        bicie++;

                    }
                }

                cout << endl;

                //Sprawdzanie ruchow po wolnych polach

                cout << "\nMozliwe ruchy: \n";

                if (Szach[px - 1][py + 1] == 3)
                {
                    cout << " 5 DL: " << "(" << px - 1 << "," << py + 1 << ")        ";
                    licznik_ruchow++;
                }

                if (Szach[px + 1][py + 1] == 3)
                {
                    cout << " 6 DR: " << "(" << px + 1 << "," << py + 1 << ")        ";
                    licznik_ruchow++;
                }

                if (Szach[px - 1][py - 1] == 3)
                {
                    cout << " 7 UL: " << "(" << px - 1 << "," << py - 1 << ")        ";
                    licznik_ruchow++;
                }

                if (Szach[px + 1][py - 1] == 3)
                {
                    cout << " 8 UR: " << "(" << px + 1 << "," << py - 1 << ")        ";
                    licznik_ruchow++;
                }

                // Gdy nie ma zadnego ruchu i bicia
                if (licznik_ruchow - 1 == 0 && bicie == 0)
                {
                    cout << " X Brak ruchow dla tego pionka\n";
                    Sleep(100);
                    goto Poczatek;
                }
                else
                {
                    cout << " 9 - cofnij        ";
                    cout << "\nWpisz ktory ruch chcesz wykonac: ";
                    cin >> ruch;

                    // BICIA czarne
                    if (ruch == 1)
                    {
                        std::swap(Szach[px - 2][py - 2], Szach[px][py]);
                        Szach[px - 1][py - 1] = 3;
                    }

                    if (ruch == 2)
                    {
                        std::swap(Szach[px - 2][py + 2], Szach[px][py]);
                        Szach[px - 1][py + 1] = 3;
                    }

                    if (ruch == 3)
                    {
                        std::swap(Szach[px + 2][py - 2], Szach[px][py]);
                        Szach[px + 1][py - 1] = 3;
                    }

                    if (ruch == 4)
                    {
                        std::swap(Szach[px + 2][py + 2], Szach[px][py]);
                        Szach[px + 1][py + 1] = 3;
                    }

                    //RUCHY czarne
                    if (ruch == 5)
                    {
                        std::swap(Szach[px - 1][py + 1], Szach[px][py]);
                    }

                    if (ruch == 6)
                    {
                        std::swap(Szach[px + 1][py + 1], Szach[px][py]);
                    }

                    if (ruch == 8)
                    {
                        std::swap(Szach[px + 1][py - 1], Szach[px][py]);
                    }

                    if (ruch == 7)
                    {
                        std::swap(Szach[px - 1][py - 1], Szach[px][py]);
                    }

                    if (ruch == 9)
                    {
                        goto Poczatek;
                    }
                }
            }
            else
            {
                cout << "Wybierz czarny pionek!";
                Sleep(150);
                goto Poczatek;
            }
    }
   
};

void Sprawdzanie()
{
    int sum1 = 0;
    int sum2 = 0;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (Szach[x][y] == 1)
            {
                sum1++;
            }

            if (Szach[x][y] == 2)
            {
                sum2++;
            }
        }
    }

    if (sum1 == 0)
        wygrana_b = 1;

    if (sum2 == 0)
        wygrana_c = 1;
}
 
void Sprawdzanie_Remis()
{
    int sumr1 = 0;
    int sumr2 = 0;

    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (Szach[x][y] == 1)
            {
                sumr1++;
            }

        }
    }

    for (int y = 1; y < 4; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (Szach[x][y] == 2)
            {
                sumr2++;
            }

        }
    }

    if (sumr1 == 12 && sumr2 == 12)
        remis = 1;
}

void Gra_Dwoch() 
{
    Szachownica szach;
    Pionki pion;

    int zaczyna = 0;
    cout << " Zdecyduj kto zaczyna" << endl;
    cout << "  0 - biale" << endl;
    cout << "  1 - czarne" << endl << endl << " Twoj wybor > ";
    cin >> zaczyna;

    tura = zaczyna;
    Sleep(100);
    system("cls");

    do
    {

        if (tura % 2 == 0)
        {
            // biale
            szach.Wyświetl();
            cout << "            >> Tura BIALE <<";
            pion.Ruch_Pionka_bialy();
            Sprawdzanie();
            system("cls");
            tura++;
        }
        else
        {
            //czarne
            szach.Wyświetl();
            cout << "            >> Tura CZARNE <<";
            pion.Ruch_Pionka_czarny();
            Sprawdzanie();
            system("cls");
            tura++;
        }

        Sprawdzanie_Remis();

    } while (wygrana_b == 0 && wygrana_c == 0 && remis == 0);

    if (wygrana_b == 1)
    {
        system("cls");
        cout << " G R A T U L A C J E ";
        cout << "\n\n > Wygraly biale < \n";
        Sleep(1000);
    }

    if (wygrana_c == 1)
    {
        system("cls");
        cout << " G R A T U L A C J E ";
        cout << "\n\n > Wygraly czarne < \n";
        Sleep(1000);
    }

    if (remis == 1)
    {
        system("cls");
        cout << " R E M I S ";
        cout << "\n\n > Nikt nie wygral :x < \n";
        Sleep(1000);
    }
}

int main()
{
    int wybor=0;
   
    while(wybor != 3)
    {
        system("cls");

        cout << " +-----------------------+" << endl;
        cout << " |         MENU          |" << endl;
        cout << " |  1 - -----            |" << endl;
        cout << " |  2 - Graj w 2 osoby   |" << endl;
        cout << " |  3 - Wyjscie          |" << endl;
        cout << " +-----------------------+" << endl;

        cout << "\n Twoj wybor : ";
        cin >> wybor;

        switch (wybor)
        {
        case 1:
            system("cls");
            break;

        case 2:
            system("cls");
            Gra_Dwoch();
            break;

        case 3:
            system("cls");
            cout << " Wylaczanie ...\n";
            exit(0);
            break;
        }
    }
    
    
}