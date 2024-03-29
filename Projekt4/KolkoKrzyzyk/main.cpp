#include <iostream>
#include <Windows.h>
#include <time.h>
#include <cstdlib>
#include <string>

#include <algorithm>
#include <limits>

#define MAX 30			// MAKSYMALNY ROZMIAR PLANSZY
#define GLEBOKOSC 10	// GLEBOKOSC PRZESZUKIWANIA
#define inf 2147483647

using namespace std;

/*--------------------*/
/*		ZMIENNE		  */
/*--------------------*/

// KLASA I METODY
int wygrana_gracz = 0;
int wygrana_komputer = 0;
int remis = 0;

int tura = 0;
int gracz1 = 1;
int gracz2 = 2;
int x, y;

int liczba_pol;				// LICZBA DEFINIOWANYCH POL
int liczba_symboli;			// LICZBA SYMBOLI POTRZEBNYCH DO WYGRANIA

// MINIMAX
int kompx = 0;
int kompy = 0;
int wynik;

// MAIN
int wybor;

/*--------------------------*/
/*		KLASA I METODY		*/	
/*--------------------------*/

class KolkoIKrzyzyk
{
private:

	int plansza[MAX][MAX];		// TWORZENIE PLANSZY

public:

	// TWORZENIE PLANSZY I ZMIENIENIE ZAWARTOSCI NA 99
	KolkoIKrzyzyk()
	{
		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				plansza[i][j] = 99;
			}
		}
	}

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

		if (liczba_pol < 1)
		{
			cout << "\n ! Liczba pol nie moza byc mniejsza niz 1 ! \n";
			goto Ponow;
		}

		if (liczba_symboli < 1)
		{
			cout << "\b !! Liczba symboli w rzedzie nie moze byc mniejsza niz 1 !! \n";
			goto Ponow;
		}

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

		// RUCHY GRACZA PIERWSZEGO
		if(tura % 2 ==0 )
		{ 
			cout << "\nWybrano: (" << x << "," << y << ")";
			plansza[x][y] = gracz1;
		}
		// RUCHY GRACZA DRUGIEGO |TESTY| - ZAKOMENTOWAC
		else
		{
			cout << "\nWybrano: (" << x << "," << y << ")";
			plansza[x][y] = gracz2;
		}
	}
	
	// SPRAWDZANIE
	int Sprawdzanie()
	{	
		/*-----------------------------------*/
		// GRACZ NUMER JEDEN - SPRAWDZANIE
		/*-----------------------------------*/
		// SPRAWDZANIE CO TURE DLA 1 GRACZA
		
			int pomg;

			// SPRAWDZANIE
			for (int a = 0; a < liczba_pol; a++)
			{
				for (int b = 0; b < liczba_pol; b++)
				{
				// SPRAWDZANIE POZIOMO
					pomg = 0;
					// SPRAWDZANIE GRACZ (POZIOMO)
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[a][b + k] == gracz1) pomg++;
					}
					if (pomg == liczba_symboli) return 1;

				// SPRAWDZANIE PIONOWO
					pomg = 0;
					// SPRAWDZANIE GRACZ (PIONOWO)
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[b + k][a] == gracz1) pomg++;
					}
					if (pomg == liczba_symboli) return 1;

				// SPRAWDZANIE SKOS 1
					// SPRAWDZANIE GRACZ UKOS 1 - POD PRZEKATNA I PRZEKATNA
					pomg = 0;
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[a + b + k][b + k] == gracz1) pomg++;
					}
					if (pomg == liczba_symboli) return 1;

					// SPRAWDZANIE GRACZ UKOS 1 - NAD PRZEKATNA I PRZEKATNA
					pomg = 0;
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[b + k][a + b + k] == gracz1) pomg++;
					}
					if (pomg == liczba_symboli) return 1;
				}
			}

			// SPRAWDZANIE SKOS 2
			for (int a = liczba_pol - 1; a > -1; a--)
			{
				for (int b = 0; b < liczba_pol; b++)
				{
				// SPRAWDZANIE GRACZ UKOS 2 - PRZEKATNA NAD I POD
					pomg = 0;
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[b + k][a - k] == gracz1) pomg++;
					}
					if (pomg == liczba_symboli) return 1;
				}
			}
			
	

		/*------------------------------------------*/
		// GRACZ NUMER DWA (KOMPUTER) - SPRAWDZANIE
		/*------------------------------------------*/
		// SPRAWDZANIE CO TURE DLA 2 GRACZA

			for (int a = 0; a < liczba_pol; a++)
			{
				for (int b = 0; b < liczba_pol; b++)
				{
				// SPRAWDZANIE POZIOMO
					pomg = 0;
				// SPRAWDZANIE GRACZ (POZIOMO)
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[a][b + k] == gracz2) pomg++;
					}
					if (pomg == liczba_symboli) return -1;

				// SPRAWDZANIE PIONOWO
					pomg = 0;
					// SPRAWDZANIE GRACZ (PIONOWO)
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[b + k][a] == gracz2) pomg++;
					}
					if (pomg == liczba_symboli) return -1;

				// SPRAWDZANIE SKOS 1
					// SPRAWDZANIE GRACZ UKOS 1 - POD PRZEKATNA I PRZEKATNA
					pomg = 0;
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[a + b + k][b + k] == gracz2) pomg++;
					}
					if (pomg == liczba_symboli) return -1;

					// SPRAWDZANIE GRACZ UKOS 1 - NAD PRZEKATNA I PRZEKATNA
					pomg = 0;
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[b + k][a + b + k] == gracz2) pomg++;
					}
					if (pomg == liczba_symboli) return -1;
				}
			}

			// SPRAWDZANIE SKOS 2
			for (int a = liczba_pol - 1; a > -1; a--)
			{
				for (int b = 0; b < liczba_pol; b++)
				{
					// SPRAWDZANIE GRACZ UKOS 2 - PRZEKATNA NAD I POD
					pomg = 0;
					for (int k = 0; k < liczba_symboli; k++)
					{
						if (plansza[b + k][a - k] == gracz2) pomg++;
					}
					if (pomg == liczba_symboli) return -1;
				}
			}

		// SPRAWDZANIE REMISU
		int rem = 0;

		for (int i = 0; i < liczba_pol; i++)
		{
			for (int j = 0; j < liczba_pol; j++)
			{
				if (plansza[i][j] == 0) rem++;
			}
		}
		if (rem == 0) 
			return 3;
		else
			return 0;
	}

	/*-----------------*/
	/*     MINIMAX     */
	/*-----------------*/

// ALGORYTM MINIMAX

	// FUNKCJA MAKSYMALIZUJACA

	int MinIMax(int glebokosc, bool maksymalizacja)
	{
		int pom = Sprawdzanie();

		// WYGRANA
		if (pom == 1) return 10;
		// PRZEGRANA
		if (pom == -1) return -10;
		//REMIS
		if (pom == 3) return 0;

		if (glebokosc == GLEBOKOSC) return pom;

		if (maksymalizacja)
		{	
			// FUNKCJA MAKSYMALIZUJACA

			int Najlepszy_wynik = -inf;

			for (int i = 0; i < liczba_pol; i++)
			{
				for (int j = 0; j < liczba_pol; j++)
				{
					if (plansza[i][j] == 0)
					{
						plansza[i][j] = gracz1;
						wynik = MinIMax(GLEBOKOSC + 1, false);
						plansza[i][j] = 0;
						Najlepszy_wynik = max(wynik,Najlepszy_wynik);
					}
				}
			}
			return Najlepszy_wynik;
		}
		else
		{
			// FUNKCJA MINIMALIZUJACA

			int Najlepszy_wynik = inf;

			for (int i = 0; i < liczba_pol; i++)
			{
				for (int j = 0; j < liczba_pol; j++)
				{
					if (plansza[i][j] == 0)
					{
						plansza[i][j] = gracz2;
						wynik = MinIMax(GLEBOKOSC + 1, true);
						plansza[i][j] = 0;
						Najlepszy_wynik = min(wynik,Najlepszy_wynik);
					}
				}
			}
			return Najlepszy_wynik;
		}
	}

	// RUCH KOMPUTERA
	void Najlepszy_ruch()
	{
		wynik = 0;
		int Najlepszy_wynik = -inf;

		for (int i = 0; i < liczba_pol; i++)
		{
			for (int j = 0; i < liczba_pol; j++)
			{
				if (plansza[i][j] == 0)
				{
					plansza[i][j] = gracz1;

					if (Sprawdzanie() == 1) wynik = inf;
					else wynik = MinIMax( 0, false);

					plansza[i][j] = 0;
					if (wynik > Najlepszy_wynik)
					{
						Najlepszy_wynik = wynik;
						kompx = i; kompy = j;
					}
				}
				else if (plansza[i][j] == 99) break;
			}
		}
		plansza[kompx][kompy] = gracz2;
	}

};

/*-----------------*/
/*       GRA       */ 
/*-----------------*/

// WYSWIETLA INFORMACJE KTO WYGRAL/ O REMISIE
void InformacjaKoncowa()
{
	getchar();

	if (wygrana_gracz == 1)
	{
		//system("cls");
		cout << " " << liczba_symboli << " razy X w rzedzie!\n";
		cout << "\n Gratulacje\n";
		cout << " WYGRALES! C:\n";
	}

	if (wygrana_komputer == 1)
	{
		//system("cls");
		cout << " " << liczba_symboli << " razy O w rzedzie!\n";
		cout << "\n Niestety\n";
		cout << " Wygral przeciwnik :C\n";
	}

	if (remis == 1)
	{
		//system("cls");
		cout << " Remis\n";
		cout << " Nikt nie wygral, nikt nie przegral\n";
	}
}

// GRA Z INNYM GRACZEM
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

			// SPRAWDZANE JEST DOPIERO OD KIEDY JEDNA OSOBA WYKONA MINIMALNA ILOSC RUCHOW BY WYGRAC
			if (tura + 1 >= (2 * liczba_symboli - 1))
			{
				if (kik.Sprawdzanie() == 1)
					wygrana_gracz = 1;
				else if (kik.Sprawdzanie() == -1)
					wygrana_komputer = 1;
				else if (kik.Sprawdzanie() == 3)
					remis = 1;
			}
			tura++;

		}
		else
		{
			// RUCHY GRACZA DRUGIEGO
			cout << " < Tura 2 gracza\n";
			kik.Ruch_Gracz();

			// SPRAWDZANE JEST DOPIERO OD KIEDY JEDNA OSOBA WYKONA MINIMALNA ILOSC RUCHOW BY WYGRAC
			if (tura + 1 >= (2 * liczba_symboli - 1))
			{ 
				if (kik.Sprawdzanie() == 1)
					wygrana_gracz = 1;
				else if (kik.Sprawdzanie() == 2)
					wygrana_komputer = 1;
				else if (kik.Sprawdzanie() == 3)
					remis = 1;
			}	
			tura++;
		} 

		kik.Wyswietl();

	} while (wygrana_gracz == 0 && wygrana_komputer==0 && remis==0);

	InformacjaKoncowa();
}

// GRA Z KOMPUTEREM
void Gra()
{
	int kto_zaczyna;

	// TWORZENIE PLANSZY I INICJACJA
	KolkoIKrzyzyk kik2;
	
Ponownie:
	system("cls");
	cout << " Kto ma zaczynac?\n";
	cout << " 1 - Gracz\n";
	cout << " 2 - Komputer\n";
	cout << "\n Twoj wybor: ";
	cin >> kto_zaczyna;
	
	if (kto_zaczyna == 1);
	else if (kto_zaczyna == 2)
		tura++;
	else
	{
		cout << "\n Podaj poprawna cyfre \n";
		Sleep(250);
		goto Ponownie;
	}

	system("cls");

	kik2.Start();
	kik2.Inicjuj();

	kik2.Wyswietl();
	do
	{
		// TURY GRACZY
		if (tura % 2 == 0)
		{
			// RUCHY GRACZA PIERWSZEGO
			cout << " > Tura 1 gracza\n";
			kik2.Ruch_Gracz();

			if (kik2.Sprawdzanie() == 1)
				wygrana_gracz = 1;
			else if (kik2.Sprawdzanie() == -1)
				wygrana_komputer = 1;
			else if (kik2.Sprawdzanie() == 3)
				remis = 1;

			tura++;

		}
		else
		{
			// RUCHY GRACZA DRUGIEGO
			cout << " < Tura 2 gracza\n";
			kik2.Najlepszy_ruch();

			if (kik2.Sprawdzanie() == 1)
				wygrana_gracz = 1;
			else if (kik2.Sprawdzanie() == -1)
				wygrana_komputer = 1;
			else if (kik2.Sprawdzanie() == 3)
				remis = 1;

			tura++;
		}

		kik2.Wyswietl();

	} while (wygrana_gracz == 0 && wygrana_komputer == 0 && remis == 0);

	InformacjaKoncowa();
}

/*------------------*/
/*       MAIN       */
/*------------------*/

void menu()
{
   cout << " +-+-+-+-+-+-+-+-+-+-+ \n"
		<< " |                   | \n"
		<< " |        MENU       | \n"
		<< " |                   | \n"
		<< " +-+-+-+-+-+-+-+-+-+-+ \n"
		<< " |                   | \n"
		<< " |      1 - Gra      | \n"
		<< " |  2 - Gra 2 osoby  | \n"
		<< " |    3 - Wyjscie    | \n"
		<< " |                   | \n"
		<< " +-+-+-+-+-+-+-+-+-+-+ \n";

   cout << "\n Twoj wybor : ";
	
}

int main()
{
	PonownieMenu:
	system("cls");
	menu();
	cin >> wybor;

	switch (wybor)
	{
		case 1:
			system("cls");
			Gra();
		break;

		case 2:
			system("cls");
			Gra_N();
		break;

		case 3:
			cout << "\n Zamykanie . . .\n";
			exit(0);
		break;

		default:
			cout << "\n Podaj poprawna liczbe ";
			Sleep(250);
			goto PonownieMenu;
		break;

	}

	return 0;
}