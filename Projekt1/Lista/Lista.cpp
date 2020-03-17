#include "lista.h"

#include <iostream>
#include <list>

#define RANGE 100

using namespace std;

void print(std::list<int> lista) {
	while (!lista.empty())
	{
		cout << lista.front() << " ";
		lista.pop_front();
	}
}

int main()
{

	std::list<int> lista;


	char x = 0;
	int r, pom, pom1, i;

	cout << "                   MENU - lista \n";
	cout << " (a) wyswietlanie zawartosci listy\n"
		<< " (b) wyswietlenie liczby elementow listy\n"
		<< " (c) wyswietlenie ostatniego elementu listy\n"
		<< " (d) wyswietlenie pierwszego elementu listy\n"
		<< " (l) dodanie losowego elementu na poczatku listy\n"
		<< " (f) dodanie losowego elementu na koncu listy\n"
		<< " (g) dodanie k elementow na poczatku listy\n"
		<< " (h) dodanie l elementow na koncu listy\n"
		<< " (i) usuwanie elementu na koncu listy\n"
		<< " (j) usuwanie j elementów na koncu listy\n"
		<< " (k) usuwanie wszystkich elementów z listy\n\n"
		<< " |e| wyjscie z programu \n\n";

	while (x != 101) {
		switch (x = getchar())
		{
			case 'a':	
				if (lista.empty() != 1)
				{
					print(lista);
					cout << "\n";
				}
				else
					cout << ">> Lista jest pusta\n";
				break;


			case 'b':
					cout << "Ilosc elementow listy: " << lista.size() << '\n';
				break;

			case 'c':
				if (lista.empty() != 1)
					cout << "Ostatni element listy: " << lista.back() << '\n';
				else
					cout << "Brak elementow na liscie\n";
				break;

			case 'd':
				if (lista.empty() != 1)
					cout << "Pierwszy element listy: " << lista.front() << '\n';
				else
					cout << "Brak elementow na liscie\n";
				break;

			case 'l':
				r = rand() % RANGE;
				lista.push_front(r);
				break;

			case 'f':
				r = rand() % RANGE;
				lista.push_back(r);
				break;
			
			case 'g':
				cout << "Podaj liczbe powtorzen: ";
				cin >> pom;
				for (i = 0; i < pom; i++)
				{
					r = rand() % RANGE;
					lista.push_front(r);
				}
				break;
			
			case 'h':
				cout << "Podaj liczbe powtorzen: ";
				cin >> pom;
				for (i = 0; i < pom; i++)
				{
					r = rand() % RANGE;
					lista.push_back(r);
				}
				break;
			
			case 'i':
				if (lista.empty() == 1)
				{
					cout << "Brak elementow na liscie\n";
					break;
				}
				else
					lista.pop_back();
				break;
			
			case 'j':
				if (lista.empty() == 1)
				{
					cout << "Brak elementow na liscie\n";
					break;
				}
				else
				{
					cout << "Podaj liczbe powtorzen: ";
					cin >> pom1;
					for (i = 0; i < pom1; i++)
					{
						if (lista.empty() == 1) {
							cout << "Lista jest juz pusta - liczba usuniec wieksza niz liczba elementow listy\n";
							break;
						}
						else
							lista.pop_back();
					}
				}
				break;
			
			case 'k':
				if (lista.empty() != 1)
					lista.clear();
				else
					cout << "Brak elementow na liscie\n";
				break;


		}

	}
	return 0;
}