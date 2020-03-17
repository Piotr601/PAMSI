#include "StosIMPL.h"
#include <iostream>
#include <cstdlib>


#define START 5

using namespace std;

class Stos {
private:
	int head;

public:
	int tab[START];

	Stos() {
		head = -1;
	}


	void push(int i);
	void pop();
	bool empty();
	int top();
	int size();
};


void Stos::push(int i) {

	if ((START - 1) <= head)
	{
		//cout << "Stos przepelniony ";  // Zrobiæ by tablica powiekszala sie 
		int pom[2 * START];	
		
		for (int j = 0; j < head; j++)
		{
			pom[j] = tab[j];
			tab[j] = pom[j];
		}

		tab[++head] = i;			// Stos dziala tylko do 12 cyfr, z czego nie wiem dlaczego pod 8 elementem wyrzuca duza liczbe
	}
	else
		tab[++head] = i;
}

void Stos::pop() {
	if (head < 0)
		cout << "Brak elementow na stosie";
	else
		int x = tab[head--];
}

bool Stos::empty() {
	return (head < 0);
}

int Stos::top() {
	cout << (tab[head]);
	return 0;
}

int Stos::size() {
	cout << (head+1);
	return 0;
}

// @@@@@@@@@@@@@@@@@@@@@@@@
//			MAIN
// @@@@@@@@@@@@@@@@@@@@@@@@

int main()
{
	int a;
	char x = 0;
	
	cout << "              Menu              \n"
		<< "(a) dodawanie elementu na stos\n"
		<< "(b) usuwanie elementu ze stosu\n"
		<< "(c) czytanie i wyswietlanie zawartosci elementu na szczycie stosu\n"
		<< "(d) sprawdzanie czy stos nie jest pusty\n"
		<< "(e) wyswietlanie liczby elementow na stosie\n\n"
		<< "(f) wyjscie z programu\n\n";
	
	Stos s;	
	
	while (x != 102) {
		switch(x = getchar()){
			case 'a':
				cout << "Podaj element, ktory zostanie dodany na stos: ";
				cin >> a;
				s.push(a);
				break;

			case 'b':
				if (s.empty() != 1)
					s.pop();
				else
					cout << "Stos pusty\n";
				break;

			case 'c':
				if (s.empty() != 1)
					s.top();
				else
					cout << "Stos jest pusty\n";
				break;

			case 'd':
				if (s.empty() != 1)
					cout << "Stos NIE JEST pusty\n";
				else
					cout << "Stos jest pusty\n";
				break;

			case 'e':
					s.size();
					cout << "\n";
				break;

		}

	}

	return 0;
}