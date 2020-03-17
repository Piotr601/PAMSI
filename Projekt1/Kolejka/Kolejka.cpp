#include "Kolejka.h"

#include <iostream>
#include <list>

#define RANGE 100

using namespace std;

void print(std::queue<int> kolejka) {
	while (!kolejka.empty())
	{
		cout << kolejka.front() << " ";
		kolejka.pop();
	}
}

int main()
{

	std::list<int> lista;


	char x = 0;
	int r, pom, pom1, i;

	cout << "                   MENU - lista \n";
	cout << " (a) wyswietlanie zawartosci listy\n"
		<< " (b) wyswietlenie liczby elementów listy\n"
		<< " (c) wyswietlenie ostatniego elementu listy\n"
		<< " (d) wyswietlenie pierwszego elementu listy\n"
		<< " (e) dodanie losowego elementu na poczatku listy\n"
		<< " (f) dodanie losowego elementu na koncu listy\n"
		<< " (g) dodanie k elementów na poczatku listy\n"
		<< " (h) dodanie l elementów na koncu listy\n"
		<< " (i) usuwanie elementu na koncu listy\n"
		<< " (j) usuwanie j elementów na koncu listy\n"
		<< " (k) usuwanie wszystkich elementów z listy\n\n"
		<< " <e> wyjscie z programu \n\n";

	while (x != 101) {
		switch (x = getchar())
		{
			case 'a':	// dodanie na koniec kolejki elementu
				r = rand() % RANGE;
				kolejka.push(r);
				break;
				
			case 'r':	// dodanie kilku elementow na koniec kolejki
				cout << "Podaj liczbe powtorzen: ";
				cin >> pom;
				for (i = 0; i < pom; i++)
				{
					r = rand() % RANGE;
					kolejka.push(r);
				}
				break;

			case 'd':	// usuniecie pierwszego elementu z kolejki
				if (kolejka.empty() == 1)
				{
					cout << "Brak elementow w kolejce\n";
					break;
				}
				else
					kolejka.pop();
					break;
		
			case 'k':	// usuniecie k elementow z poczatku kolejki
				if (kolejka.empty() == 1)
				{
					cout << "Brak elementow w kolejce\n";
					break;
				}
				else
				{
					cout << "Podaj liczbe powtorzen: ";
					cin >> pom1;
					for (i = 0; i < pom1; i++)
					{
						if (kolejka.empty() == 1) {
							cout << "Kolejka jest juz pusta - liczba usuniec wieksza niz liczba elementow kolejki\n";
							break;
						}
						else
							kolejka.pop();
					}
				}

			case 's': // wyœwietla kolejke
				if (kolejka.empty() != 1)
				{
					print(kolejka);
					cout << "\n";
				}
				else
					cout << ">> Kolejka jest pusta\n";
				break;

			case 'n': //wyswietla liczbe elementow na stosie
				cout << "> Liczba elementow kolejki: " << kolejka.size() << "\n";
				break;

			case 't': // sprawdzanie poczatku kolejki
				if (kolejka.empty() == 1)
				{
					cout << "Brak elementow w kolejce\n";
				}
				else
					cout << " > Pierwszy element kolejki: " << kolejka.front() << "\n";
				break;
		}




	}

	return 0;
}