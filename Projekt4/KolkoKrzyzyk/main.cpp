#include <iostream>
#include <Windows.h>
#include <time.h>
#include <cstdlib>

#define MAX 50			// MAKSYMALNY ROZMIAR PLANSZY

using namespace std;

/*--------------------*/
/*		ZMIENNE		  */
/*--------------------*/

int wygrana_gracz = 0;
int wygrana_komputer = 0;
int tura = 0;
int gracz1 = 1;
int gracz2 = 2;
int x, y;

/*--------------------------*/
/*		KLASA I METODY		*/	
/*--------------------------*/

class KolkoIKrzyzyk
{
private:
	
	int liczba_pol;				// LICZBA DEFINIOWANYCH POL
	int liczba_symboli;			// LICZBA SYMBOLI POTRZEBNYCH DO WYGRANIA
	int plansza[MAX][MAX];		// TWORZENIE PLANSZY

public:

	// INICJOWANIE PLANSZY
	void Inicjuj()
	{
		for (int i = 0; i < liczba_pol; i++)
		{
			for (int j = 0; j < liczba_pol; j++)
			{
				plansza[i][j] = 0;
			}
		}
	}
	
	// WYSWIETLANIE PLANSZY
	void Wyswietl()
	{
		system("cls");
		// WYSWIETLENIE INDEKSOW GORA
		cout << "  ";
		for (int i = 0; i < liczba_pol; i++)
			cout << "   " << i;

		// WYSWIETLENIE OBRAMOWANIA
		cout << "\n   +";
		for (int i = 0; i < liczba_pol; i++)
			cout << "---+";

		cout << endl;

		// WYSWIETLENIE PLANSZY I INDEKSOW
		for (int i = 0; i < liczba_pol; i++)
		{
			cout << " " << i << " |";
			for (int j = 0; j < liczba_pol; j++)
			{
				// WYSWIETLANIE W ZALEZNOSCI OD ZNAKU NA POLU
				if (plansza[i][j] == gracz1)
					cout << " " << "X" << " |";
				else if (plansza[i][j] == gracz2)
					cout << " " << "O" << " |";
				else 
					cout << " " << " " << " |";
			}
			cout << endl;
		}

		// WYSWIETLENIE OBRAMOWANIA DOL
		cout << "   +";
		for (int i = 0; i < liczba_pol; i++)
			cout << "---+";

		cout << endl;
	}	

	// START GRY, ZCZYTYWANIE ILOSCI POL
	void Start()
	{
		cout << " Witaj w grze kolko i krzyzyk\n";
		Ponow:
		cout << "\n > Zdefiniuj ile pol ma miec plansza\n";
		cout << " Liczba pol : ";
		cin >> liczba_pol;
		cout << "\n Zdefiniuj ile symboli w rzedzie wygrywa\n";
		cout << " Liczba symboli : ";
		cin >> liczba_symboli;

		//! DOPISAC BY WARTOSCI NIE BYLY UJEMNE 
		if (liczba_symboli > liczba_pol)
		{
			cout << "\n !!! Liczba symboli w rzedzie jest wieksza niz rozmiar planszy, sprobuj ponownie !!! \n";
			goto Ponow;
		}

		system("cls");
	}

	// RUCH GRACZA
	void Ruch_Gracz()
	{
		do {

			char temp;
			cout << " > Podaj wspolrzedne w ktorym chcesz wstawic znak np. (1,1) : ";
			cin >> temp >> x >> temp >> y >> temp;

		} while (plansza[x][y] != 0);

		if(tura % 2 ==0 )
		{ 
			cout << "\nWybrano: (" << x << "," << y << ")";
			plansza[x][y] = gracz1;
		}
		else
		{
			cout << "\nWybrano: (" << x << "," << y << ")";
			plansza[x][y] = gracz2;
		}
	}

	// SPRAWDZANIE
	void Sprawdzanie(int x, int y)
	{	/*-----------------------------------*/
		// GRACZ NUMER JEDEN - SPRAWDZANIE
		/*-----------------------------------*/
		if (tura % 2 == 0)
		{
			// SPRAWDZANE JEST DOPIERO OD KIEDY JEDNA OSOBA WYKONA MINIMALNA ILOSC RUCHOW BY WYGRAC
			if (tura+1 >= (2 * liczba_symboli - 1))
			{
				int pomg;
				// SPRAWDZANIE POZIOMO
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					// SPRAWDZANIE GRACZ (POZIOMO)
					if (plansza[x][a] == gracz1) pomg++;
					else pomg = 0;

					if (pomg == liczba_symboli) wygrana_gracz = 1;
				}

				// SPRAWDZANIE PIONOWO
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					// SPRAWDZANIE GRACZ (PIONOWO)
					if (plansza[a][y] == gracz1) pomg++;
					else pomg = 0;

					if (pomg == liczba_symboli) wygrana_gracz = 1;
				}

				// SPRAWDZANIE SKOS 1

					// SPRAWDZANIE GRACZ UKOS 1 - POD PRZEKATNA I PRZEKATNA
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					for (int b = 0; b < liczba_pol; b++)
					{
						if (plansza[b + a][b] == gracz1) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_gracz = 1;
					}
				}

				// SPRAWDZANIE GRACZ UKOS 1 - NAD PRZEKATNA I PRZEKATNA
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					for (int b = 0; b < liczba_pol; b++)
					{
						if (plansza[b][b + a] == gracz1) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_gracz = 1;
					}
				}

				// SPRAWDZANIE SKOS 2

					// SPRAWDZANIE GRACZ UKOS 2 - NAD PRZEKATNA I PRZEKATNA ODWROTNA
				pomg = 0;
				for (int a = liczba_pol - 1; a > -1; a--)
				{
					for (int b = 0; b < liczba_pol; b++)
					{
						if (plansza[b][a - b] == gracz1) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_gracz = 1;
					}
				}

				// SPRAWDZANIE GRACZ UKOS 2 - POD PRZEKATNA I PRZEKATNA ODWROTNA
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					for (int b = liczba_pol - 1; b > -1; b--)
					{
						if (plansza[b][liczba_pol - b + a] == gracz1) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_gracz = 1;
					}
				}
			}
		}
		/*------------------------------------------*/
		// GRACZ NUMER DWA (KOMPUTER) - SPRAWDZANIE
		/*------------------------------------------*/
		else 
		{
			// SPRAWDZANE JEST DOPIERO OD KIEDY OSOBA WYKONA MINIMALNA ILOSC RUCHOW BY WYGRAC
			if (tura+1 >= (2 * liczba_symboli - 1))
			{
				int pomg;
				// SPRAWDZANIE POZIOMO
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					// SPRAWDZANIE GRACZ (POZIOMO)
					if (plansza[x][a] == gracz2) pomg++;
					else pomg = 0;

					if (pomg == liczba_symboli) wygrana_komputer = 1;
				}

				// SPRAWDZANIE PIONOWO
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					// SPRAWDZANIE GRACZ (PIONOWO)
					if (plansza[a][y] == gracz2) pomg++;
					else pomg = 0;

					if (pomg == liczba_symboli) wygrana_komputer = 1;
				}

				// SPRAWDZANIE SKOS 1

					// SPRAWDZANIE GRACZ UKOS 1 - POD PRZEKATNA I PRZEKATNA
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					for (int b = 0; b < liczba_pol; b++)
					{
						if (plansza[b + a][b] == gracz2) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_komputer = 1;
					}
				}

				// SPRAWDZANIE GRACZ UKOS 1 - NAD PRZEKATNA I PRZEKATNA
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					for (int b = 0; b < liczba_pol; b++)
					{
						if (plansza[b][b + a] == gracz2) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_komputer = 1;
					}
				}

				// SPRAWDZANIE SKOS 2

					// SPRAWDZANIE GRACZ UKOS 2 - NAD PRZEKATNA I PRZEKATNA ODWROTNA
				pomg = 0;
				for (int a = liczba_pol - 1; a > -1; a--)
				{
					for (int b = 0; b < liczba_pol; b++)
					{
						if (plansza[b][a - b] == gracz2) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_komputer = 1;
					}
				}

				// SPRAWDZANIE GRACZ UKOS 2 - POD PRZEKATNA I PRZEKATNA ODWROTNA
				pomg = 0;
				for (int a = 0; a < liczba_pol; a++)
				{
					for (int b = liczba_pol - 1; b > -1; b--)
					{
						if (plansza[b][liczba_pol - b + a] == gracz2) pomg++;
						else pomg = 0;

						if (pomg == liczba_symboli) wygrana_komputer = 1;
					}
				}
			}
		}
	}
};

/*-----------------*/
/*       GRA       */
/*-----------------*/

void Gra_N()
{
	// TWORZENIE PLANSZY I INICJACJA
	KolkoIKrzyzyk kik;

	kik.Start();
	kik.Inicjuj();

	kik.Wyswietl();
	do
	{
		// TURY GRACZY
		if (tura % 2 == 0)
		{
			// RUCHY GRACZA PIERWSZEGO
			cout << " > Tura 1 gracza\n";
			kik.Ruch_Gracz();
			kik.Sprawdzanie(x, y);
			tura++;

		}
		else
		{
			// RUCHY GRACZA DRUGIEGO
			cout << " < Tura 2 gracza\n";
			kik.Ruch_Gracz();
			kik.Sprawdzanie(x, y);
			tura++;
		}

		kik.Wyswietl();

	} while (wygrana_gracz == 0 && wygrana_komputer == 0);

	if (wygrana_gracz == 1)
	{
		system("cls");
		cout << "Gratulacje\n";
		cout << "WYGRALES! C:\n";
	}

	if (wygrana_komputer == 1)
	{
		system("cls");
		cout << "Niestety\n";
		cout << "Wygral przeciwnik :C\n";
	}

}

/*------------------*/
/*       MAIN       */
/*------------------*/

int main()
{
	Gra_N();
	return 1;
}