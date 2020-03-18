#include "Kopiec.h"

#include <iostream>
#define MAX 100
#define RANGE 100
using namespace std;


/* I METODA

// klasa
class Kopiec {
public:
	int elem;
	Kopiec* rodz;
	Kopiec* lewys;
	Kopiec* prawys;
};

//wskaznik na korzen
	Kopiec* korzen = NULL;

// dodawanie wartosci
void dodaj(int wartosc) {

	// wskaznik na korzen
	Kopiec* wsk = korzen;
	// wskaznik na nowy korzen
	Kopiec* nowykorzen = new Kopiec;

	nowykorzen->elem = wartosc;
	nowykorzen->lewys = NULL;
	nowykorzen->prawys = NULL;

	if (korzen == NULL) {	// warunek jezeli korzen jest NULL
		nowykorzen->rodz = NULL;
		korzen = nowykorzen;
	}
	else
	{
		while (wsk != NULL)
		{
			if (wsk->prawys == NULL) {			
				nowykorzen->rodz = wsk;
				wsk->prawys = nowykorzen;
			}
			else
				wsk = wsk->lewys;

			if (wsk->lewys == NULL) {
				nowykorzen->rodz = wsk;
				wsk->lewys = nowykorzen;
			}
			else
				wsk = wsk->prawys;
		}
	}
};
void usun() {
}
int main()
{
	return 0;
}
*/

// 2 METODA

// klasa
class Heap {
public:
	Heap() { size = 0; };		// konstuktor
	
	int tab[MAX];				// tablica
	int size;					// wielkosc

	void display(int num);		// wyswietlanie
	void sort();				// sortowanie, nie dziala :<
	void del();					// usuwanie
	void add(int value);		// dodawanie wartosci
};

//  @@@@@@@@@@@@@@@@@
//		METODY
//  @@@@@@@@@@@@@@@@@@

void Heap::display(int num)
{
	if (num <= size)									// wyswietlanie od num - elementu
		cout << "Numerek: " << num << " : " << tab[num] << "\n";		// preferowane jest display(1)
	if (num*2 <= size)									
		display(num * 2);								// referencja dla lewej galezi
	if ((num*2 + 1) <= size)
		display(num * 2 + 1);							// referencja dla prawej galezi
};

// dodawanie elementow
void Heap::add(int value)
{
	int pom[MAX];					// tablica pomocnicza
	tab[size + 1] = value;
	int p = size+1;					// zmienna pomocnicza
	while (p != 1) {
		if (tab[p / 2] < tab[p])
		{
			pom[1] = tab[p];			// zamiana tablicy tab[p] <-> tab[p/2]
			tab[p] = tab[p / 2];
			tab[p / 2] = pom[1];

			p = p / 2;
		}
	}
	size++;							// powiekszanie tablicy i jej wielkosci
};

// usuwanie elementow
void Heap::del()
{
	int pom1[MAX];					// tablica pomocnicza
	tab[1] = tab[size];
	size--;

	int pom = 1;

	while (pom * 2 <= size)
	{
		if (tab[pom] < tab[pom * 2] || tab[pom] < tab[pom * 2 + 1])		// jezeli istnieje tablica dzieci (lewego lub prawego syna) to
		{
			if (tab[pom * 2] > tab[pom * 2 + 1] || pom * 2 + 1 > size)	
			{
				pom1[1] = tab[pom];					// zamiana tablicy tab[p] <-> tab[p/2]
				tab[pom] = tab[pom * 2];
				tab[pom / 2] = pom1[1];

				pom = pom * 2;
			}
			else									// w przeciwnym razie
			{
				pom1[1] = tab[pom];					// zamiana tablicy tab[p] <-> tab[p/2]
				tab[pom] = tab[pom * 2 + 1];
				tab[pom / 2] = pom1[1];

				pom = pom * 2 + 1;
			}
		}
		else
			break;
	}
};

// sortowanie, ktore nie dziala :/
void Heap::sort()
{
	for (int j = 0; j <= size; j++)
	{
		cout << tab[1] << " \n";			// wypisanie liczby
		del();								// usuniecie
	}
	cout << "Po sortowaniu"<< tab[1] << "\n";	// wypisanie po sortowaniu
};


int main()
{
	char x=0;
	int z,ile,liczba;

	Heap h;


	cout << "                             MENU            \n"
		<< "(a) // nie dziala cos budowa kopca na podstawie tablicy n losowych elementów\n"
		<< "(b) // nie dziala cos przywracanie w³asnosci kopca\n"
		<< "(c) dodanie elementu do kopca\n"
		<< "(d) usuniecie korzenia kopca\n"
		<< "(e) // :/ wyswietlenie rozmiaru kopca\n"
		<< "(f) // czytelne wyswietlanie kopca\n\n"
		<< "(g) wyjscie z programu\n\n";

	while (x != 103)	// warunek na wyjscie z programu ASCII  103 ='g'
	{
		switch (x = getchar())		// instrukcja warunkowa wyboru z menu
		{
		case 'a':
			cout << "Podaj ilosc razy: ";
			cin >> ile;
			for (int i = 0; i < ile; i++)
			{
				z = rand() % RANGE;				// losowanie wartosci
				h.add(z);
				cout << "Poprawnie\n";
			}
			break;

		case 'b':
			h.sort();
			break;

		case 'c':
			cout << " Podaj liczbe: ";
			cin >> liczba;
			h.add(liczba);
			break;

		case 'd':
			h.del();
			break;

		case 'e':
			cout << "Wielkosc kopca: ";
			break;

		case 'f':
			h.display(1);
			break;
		}
	}
}