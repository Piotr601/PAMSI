#include "Stos.h"


#include <iostream>
#include <stack>

#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

#define RANGE 100

void print(std::stack<int> stos) {
	while (!stos.empty()) {
		cout << stos.top() << " ";
		stos.pop();
	}

}

int main()
{
	std::stack<int> stos;

	char x=0;
	int r, pom, pom1, i;

	cout << "                   MENU - Stos \n";
	cout << " |-| a (add) - dodaj losowy element\n";
	cout << " |-| r (random) - dodaj r losowych elementow do stosu\n";
	cout << " |-| t (top) - sprawdz szczyt stosu i wypisz element\n";
	cout << " |-| d (delete) - usuniecie elementu na szczycie stosu\n";
	cout << " |-| k (k delete) - usuniecie k elementow ze stosu\n";
	cout << " |-| s (stack) - wyœwietl stos\n";
	cout << " |-| n (number) - ilosc liczb na stosie\n\n";
	cout << " |*| e (exit) - wyjscie z programu\n\n";

	
 while (x != 101) {
	switch (x=getchar())
	{
		case 'a':	// dodawanie do stosu losowego elementu
			r = rand() % RANGE;
			stos.push(r);
			break;

		case 'r':  // dodawanie r losowych elementów do stosu
			cout << "Podaj liczbe powtorzen: ";
			cin >> pom;
			for (i = 0; i < pom; i++)
			{
				r = rand() % RANGE;
				stos.push(r);
			}
			break;

		case 't': // sprawdzanie szczytu 
			if (stos.empty() == 1)
			{
				cout << "Brak elementow na stosie\n";
			}
			else
				cout << " > Szczyt stosu: " << stos.top() << "\n";
			break;

		case 'd': //usuniecie ze stosu
			if (stos.empty() == 1)
			{
				cout << "Brak elementow na stosie\n";
				break;
			}
			else
				stos.pop();
			break;

		case 'k': // usuniecie k ze szczytu stosu
			if (stos.empty() == 1)
			{
				cout << "Brak elementow na stosie\n";
				break;
			}
			else
			{
				cout << "Podaj liczbe powtorzen: ";
				cin >> pom1;
				for (i = 0; i < pom1; i++)
				{
					if (stos.empty() == 1) {
						cout << "Stos jest juz pusty - liczba usuniec wieksza niz liczba elementow stosu";
						break;
					}
					else
						stos.pop();
				}
			}

		case 's': // wyœwietla stos
			if (stos.empty() != 1)
			{
				print(stos);
				cout << "\n";
			}
			else
				cout << ">> Stos jest pusty\n";
			break;

		case 'n': //wyswietla liczbe elementow na stosie
			cout << "> Liczba elementow stosu: "  << stos.size() << "\n";
			break;
	}
}




	return 0;
}