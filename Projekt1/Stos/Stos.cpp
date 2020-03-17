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
	int r, pom, i;

	cout << "                   MENU - Stos \n";
	cout << " |-| a (add) - dodaj losowy element\n";
	cout << " |-| r (random) - dodaj r losowych elementow do stosu\n";
	cout << " |-| t (top) - sprawdz szczyt stosu i wypisz element\n";
	cout << " |-| d (delete) - usuniecie elementu na szczycie stosu\n";
	cout << " |-| k (k delete) - usuniecie k elementow ze stosu\n";
	cout << " |-| s (stack) - wyœwietl stos\n";
	cout << " |-| n (number) - iloœæ liczb na stosie\n\n";
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
			}
			else
				stos.pop();
			break;
	}
}



	print(stos);

	return 0;
}