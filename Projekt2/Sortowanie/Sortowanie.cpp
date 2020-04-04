#include "Sortowanie.h"
#include <iostream>


#define N 1000000	// wielkosc tablicy

/*
	Plik Sortowanie.cpp

	Plik w którym znajd¹ sie wszystkie funkcji wraz z kodem
	które bêd¹ potrzebne do sortowañ

*/

int tab[N];		// glowna tablica
int pom[N];		// tablica pomocnicza

/*
=================
	Merge sort
=================
*/


void Merge(int leftIndex, int middleIndex, int rightIndex)	// laczenie tablic
{
	int p1 = leftIndex;		  // pointer1 - wskazuje na poczatek pierwszej tablicy
	int p2 = middleIndex + 1; // pointer2 - wskazuje na poczatek drugiej tablicy
	int curr = leftIndex;	  // current - indeks, gdzie wpisujemy najmniejszy element


	for (int i = leftIndex; i <= rightIndex; i++) {		// kopiowanie tablicy
		pom[i] = tab[i];
	}

	while (p1 <= middleIndex && p2 <= rightIndex) {	// dopoki nie dojdziemy do konca 1 tab i 2 tab
		if (pom[p1] <= pom[p2]) {			// element 1 podtablicy jest mniejszy
			tab[curr] = pom[p1];			// PDTG* - przepisz do tablicy glownej
			p1++; curr++;					// ZW* - zwiekszanie indeksu
		}
		else {								// element 2 podtablicy jest mniejszy
			tab[curr] = pom[p2];			// PDTG*
			p2++; curr++;					// ZW*
		}
	}

	while (p1 <= middleIndex) {				// dopoki elementy w 1 tablicy sa
		tab[curr] = pom[p1];				// PDTG*
		curr++; p1++;						// ZW*
	}
}

int MergeSort(int leftIndex, int rightIndex)
{

	if (leftIndex < rightIndex) {					// dzielimy dopoki nie bedzie jednego elementu
		int middle = (leftIndex + rightIndex) / 2;	// srodek

		MergeSort(leftIndex, middle);				// sortujemy lewa podtablice
		MergeSort(middle + 1, rightIndex);			// sortujemy prawa podtablice

		Merge(leftIndex, middle, rightIndex);		// polaczenie podtablic
	}
	return 0;

	if (rightIndex >= leftIndex) return 1;
}


/*
==================
  Funkcje OGOLNE
==================
*/

// Tworzy losowa tablice
void Stworz()
{
	for ( int i = 0; i < N; i++ ) {
		tab[i] = rand() % N;
	}
}

// Wyswietla tablice po/przed sortowaniem
void Wyswietl()
{
	for ( int i = 0; i < N; i++ ) {
		if ( i % 25 == 0 ) std::cout << '\n';
		std::cout << tab[i] << ' ';
	}
}

// Warunek czy sortowanie dziala dobrze
int Sprawdz()
{
	for ( int i = 0; i < N; i++ ) {
		if ( i != 0 && tab[i] < tab[i - 1] ) {
			std::cout << "\n >>>> BLAD W SORTOWANIU <<<< \n";
			return 1;
		}
	}
	return 0;
}

